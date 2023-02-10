
import ctypes



# Load DLL into memory.

dll = ctypes.WinDLL("E:\\apps\\Z\\ZorroControl.dll")

dll.zInit(2,4)

dll.zOpen(2,"Strategy/Control.c -run -h -edit")

dll.zData(1)

dll.zClose(0)