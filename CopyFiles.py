#!/usr/bin/env python
# coding: utf-8

# In[14]:


import pyautogui as pag
import pyperclip as ppc
from time import sleep

a = input("选择读取内容：xx.生成告示牌；yy.替换告示牌:")
sleep(5)
print("start")
f = open( 'command.txt', 'r',encoding = 'utf-8' )
f1 = open( 'alternative.txt', 'r',encoding = 'utf-8' )
if a == "xx":
    print(a)
    for line in f.readlines():
        ppc.copy(line)
        pag.press('t')
        sleep(.3)
        pag.hotkey('ctrl','v')
        sleep(.2)
        pag.press('enter')
        sleep(.2)
elif a == "yy":
    print(a)
    for line in f1.readlines():
        ppc.copy(line)
        pag.press('t')
        sleep(.3)
        pag.hotkey('ctrl','v')
        sleep(.2)
        pag.press('enter')
        sleep(.2)
f.close()
f1.close()


# In[ ]:




