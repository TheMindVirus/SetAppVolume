import ctypes

mod = ctypes.cdll.LoadLibrary(".\\SetAppVolume.dll")
mod.SetAppVolume(0, 100)

print("Done!")
