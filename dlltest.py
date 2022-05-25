import ctypes

crossfader = 50 # A minimal crossfader for smoothly switching audio between apps

A = max(min((100 - crossfader) * 2, 100), 0)
B = max(min(crossfader * 2, 100), 0)

print(A, B) # Dock App1 Left, Dock App2 Right (0 indexed)

AppLeft = 1
AppRight = 2

mod = ctypes.cdll.LoadLibrary(".\\x64\\Release\\SetAppVolume.dll")
mod.SetAppVolume(AppLeft, A) # Optionally these can be manually balanced
mod.SetAppVolume(AppRight, B) # With 2 Physical Faders in PyGame MIDI etc...

print("Done!")
