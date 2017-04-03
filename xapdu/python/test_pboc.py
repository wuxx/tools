#!/usr/bin/env python

# APDU shell
#
# Copyright (c) 2014 Goran Rakic <grakic@devbase.net>

import sys, os, stat
import getopt
from time import sleep
from threading import Thread, Event
from subprocess import Popen, PIPE
#from fcntl import fcntl, F_GETFL, F_SETFL
from smartcard.System import readers
from smartcard.CardRequest import CardRequest
from smartcard.util import *

def error(e, lineno = None):
    out = "   Error"
    if lineno is not None:
        out += " on line %d" % lineno
    out += ": " + str(e)
    return out

class Connection(object):

    __connection = None

    class Monitoring(Thread):

        def __init__(self, observer, reader):
            Thread.__init__(self)
            self.reader = reader
            self.observer = observer
            self.stopEvent = Event()
            self.stopEvent.clear()
            self.initializedEvent = Event()
            self.initializedEvent.clear()
            self.setDaemon(True)
            self.card = None

        def run(self):
            self.cardrequest = CardRequest(timeout=0.5, readers=[reader])
            while not self.stopEvent.isSet():
                try:
                    card = self.cardrequest.waitforcardevent()
                    if card != self.card:
                        if not card:                    
                            self.observer.removed()
                        else:
                            self.observer.inserted(card[0])
                    self.card = card
                    self.initializedEvent.set()
                except Exception as e:
                    print >> sys.stderr, "Connection error:", e

    def __init__(self, reader):
        self.monitoring = Connection.Monitoring(self, reader)
        self.monitoring.start()
        while not self.monitoring.initializedEvent.isSet():
            sleep(0.1)

    def inserted(self, card):
        self.__connection = card.createConnection()
        self.__connection.connect()
        # print "Card connected: %s" % toHexString(card.atr)

    def removed(self):
        self.__connection = None
        # print "Card removed"
            
    def tx(self, sapdu, expect_sw = None):
        bapdu = []
        sapdu = sapdu.split(' ')
        for part in sapdu:
            if len(part) % 2 == 0:
                bapdu.extend([hexByteToInt(part[2*i:2*i+2]) for i in range(len(part)/2)])
            elif len(part) == 1:
                bapdu.append(hexByteToInt(part))
            else:
                raise ValueError("Input error at: '%s'" % part)

        rdata = connection.send(bapdu, None, True)
        sw = "%02x%02x" % (rdata[-2], rdata[-1])
        if (expect_sw != None):
            if expect_sw != sw:
                print "fail"
                sys.exit(-1)
            else:
                print "succ"

    def send(self, apdu, output=None, show_sent=True):
         if not self.__connection:
             raise Exception("Card not connected")

         # print input
         print ">> %s" % toHexString(apdu)

         data, sw1, sw2 = self.__connection.transmit(apdu)

         # print output and data
         print "<< %02X %02X%s" % (sw1, sw2, ", %d bytes" % len(data) if data else "")
         if data:
             if output:
                 # save data
                 with open(output, "w+") as f:
                     f.write(HexListToBinString(data))
                 print "   Output saved to %s" % output
             else:
                 # pack 8 bits into bytes, write 4 bytes per line
                 bytes = [toHexString(data[i:i+8]) for i in range(0, len(data), 8)]
                 print "\n".join(["   "+"  ".join(bytes[i:i+4]) for i in range(0, len(bytes), 4)])

         # return response
         return data + [sw1, sw2]

    def close(self):
        self.monitoring.stopEvent.set()
        self.connection = None

def hexByteToInt(byte):
    try:
        return int(byte, 16)
    except ValueError as e:
        if "invalid literal" in str(e):
            raise ValueError("Input error %s" % str(e)[-4:])
        else:
            raise

def parse(line):
    apdu = []
    line, _, output = line.partition('>')
    line = line.split(' ')
    print "line [%s]" %(line)
    for part in line:
        if len(part) % 2 == 0:
            apdu.extend([hexByteToInt(part[2*i:2*i+2]) for i in range(len(part)/2)])
        elif len(part) == 1:
            apdu.append(hexByteToInt(part))
        else:
            raise ValueError("Input error at: '%s'" % part)

    output = output.strip()
    return apdu, output or None

def select_reader(name=None, index=None):
    readers_all = readers()
    if index is None:
        for reader in readers_all:
            if name in str(reader):
                return reader
        raise Exception("Unknown reader %s" % name)
    else:
        if index < len(readers_all):
            return readers_all[index]
        else:
            raise Exception("Unknown reader number #%d" % index)

def list_readers():
    print "Listing readers:"
    for i, reader in enumerate(readers()):
        reader = str(reader)
        print " #%d" % i, reader[:60], "..." if len(reader)>60 else ""
    print

if __name__ == "__main__":

    reader = None
    list_readers()
    # Parse options
    try:
        opts, args = getopt.getopt(sys.argv[1:], "hr:l", ["help", "reader=", "list"])
    except getopt.GetoptError as e:
        print >> sys.stderr, str(e)
        sys.exit(2)
    for o, a in opts:
        if o in ("-r", "--reader"):
            reader = a
        elif o in ("-h", "--help"):
            sys.exit()
        elif o in ("-l", "--list"):
            list_readers()
            sys.exit()

    # Connect reader
    try:
        print "start"
        if not reader:
            reader = select_reader(index=0)
        elif reader.isdigit():
            reader = select_reader(index=int(reader))
        else:
            reader = select_reader(reader)

        connection = Connection(reader)

        #read UID
        rdata = connection.tx('FFCA000000', '9000')

        #select ISD
        rdata = connection.tx('00a4040000', '9000')

        #select PPSE
        rdata = connection.tx('00A40400 0E 325041592E5359532E4444463031', '9000')

        #select pboc applet (4Fxx tag of select PPSE)
        rdata = connection.tx('00A40400 08 A000000333010103', '9000')

        #read the ATC (application transaction counter)
        rdata = connection.tx('80CA9F3600', '9000')

        #read the EC balance
        rdata = connection.tx('80CA9F7900', '9000')

        #read the EC balance limit
        rdata = connection.tx('80CA9F7700', '9000')

        # read the EC balance limit per transaction
        rdata = connection.tx('80CA9F7800', '9000')

        #valid_date_start(5F25), vaild_date_end (5F24)
        #card serial num (5Axx)
        rdata = connection.tx('00 B2011400', '9000')

        rdata = connection.tx('00 B2010C00', '9000')

        # owner id (9F61), id type(9F62), name (5F20)
        rdata = connection.tx('00 B2020C00', '9000')
        print "exit"
    except Exception as e:
        print >> sys.stderr, str(e)
        sys.exit(1)