#coding=utf8
#mouse click
#windows 
import pythoncom
import pyHook

from pymouse import PyMouse
from time import sleep

m = PyMouse()
def onKeyboardEvent(event): 
 
  print "%3d" % event.KeyID,"%-10s" % event.Key,
  #print "type keyid is ",type(event.KeyID),
  #print "type key is ",type(event.Key)
  x,y = m.position()
  #print "Down"
  #x,y = event.Position
  if event.KeyID == 27:
    print "quit"
    exit(-1)
  if event.KeyID > 58 or event.KeyID < 48 :
    m.click(x ,y ,1) 
    print "\tclick  1"
    return True
  for i in range(event.KeyID-48):
    m.click(x ,y,1 )
    
    sleep(0.12)
  print "\tclick %2d " % (event.KeyID-48)
  # 返回 True 以便将事件传给其它处理程序   
  # 注意，这儿如果返回 False ，则鼠标事件将被全部拦截   
  # 也就是说你的鼠标看起来会僵在那儿，似乎失去响应了   
  return True
  
def main():   
  # 创建一个“钩子”管理对象   
  hm = pyHook.HookManager()   
   
  #监控键盘
  hm.KeyDown = onKeyboardEvent
  hm.HookKeyboard()
 
  
  #进入循环，如不手动关闭，程序将一直处于监听状态   
  pythoncom.PumpMessages() 

if __name__ == "__main__":   
  main()

