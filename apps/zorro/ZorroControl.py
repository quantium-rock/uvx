


import ctypes


# Load DLL into memory.

dll = ctypes.WinDLL("E:/apps/Z/ZorroControl.dll")

dll.zInit(2,8)

print(dll.zOpen(2,"-w 320"))

dll = ctypes.WinDLL("E:/apps/Z/chartdir60.dll")

dll.

