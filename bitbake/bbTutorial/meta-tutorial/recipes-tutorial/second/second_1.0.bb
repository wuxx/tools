DESCRIPTION = "I am he second recipe"
PR = "r1"
inherit mybuild
 
def pyfunc(o):
    #print dir (o)
    print ("hello second recipe")
 
python do_mypatch () {
    bb.note ("runnin mypatch")
    pyfunc(d)
}
 
addtask mypatch before do_build
