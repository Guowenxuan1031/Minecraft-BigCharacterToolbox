#!/usr/bin/env python
# coding: utf-8

# In[14]:


# str1 = '你好'
str1 = input("输入汉字：")
# uni = str1.encode('unicode-escape').decode()
# print(str(len(str1)) + uni + "\n")
# print()
print(str(len(str1)))
for ch in str1:
    tmp_ch = hex(ord(ch))[2:]
    print("0" * (4 - len(tmp_ch)) + tmp_ch)


# In[ ]:





# In[ ]:




