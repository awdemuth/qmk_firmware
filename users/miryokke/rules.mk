MOUSEKEY_ENABLE = yes        # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes        # Audio control and System control(+450)
EXTRAFLAGS += -flto	     # Link Time Optimization to reduce code size, 31358->28034/28672
SRC += genkeymap.c
