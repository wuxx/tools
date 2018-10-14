#!/usr/bin/env python
#coding=utf-8

#depend pywin32
import win32gui,win32api,win32con
import time
import threading

"""
      A   65       0   96        F1   112     Backspace     8 
      B   66       1   97        F2   113     Tab           9 
      C   67       2   98        F3   114     Clear         12 
      D   68       3   99        F4   115     Enter         13 
      E   69       4   100       F5   116     Shift         16 
      F   70       5   101       F6   117     Control       17 
      G   71       6   102       F7   118      Alt          18 
      H   72       7   103       F8   119     Caps Lock     20 
      I   73       8   104       F9   120     Esc           27 
      J   74       9   105       F10  121     Spacebar      32 
      K   75       *   106       F11  122     Page Up       33 
      L   76       +   107       F12  123     Page Down     34 
      M   77       Enter 108       --   --      End         35 
      N   78       -   109       --   --       Home         36 
      O   79       .   110       --   --      Left Arrow    37 
      P   80       /   111       --   --      Up Arrow      38 
      Q   81       --   --       --   --      Right Arrow   39 
      R   82       --   --       --   --      Down Arrow    40 
      S   83       --   --       --   --      Insert        45 
      T   84       --   --       --   --      Delete        46 
      U   85       --   --       --   --      Help          47 
      V   86       --   --       --   --      Num Lock     144 
"""

def thread_key():
    while True:
        time.sleep(1) #measure by second

        win32api.keybd_event(20,0,0,0)
        win32api.keybd_event(20,0,win32con.KEYEVENTF_KEYUP,0)
        
t = threading.Thread(target=thread_key)
t.start()
