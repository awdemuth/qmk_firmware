OLED_DRIVER_ENABLE = yes   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes        # Audio control and System control(+450)
EXTRAFLAGS += -flto	     # Link Time Optimization to reduce code size, 31358->28034/28672
