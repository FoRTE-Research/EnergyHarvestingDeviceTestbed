###################################################
# Build Flags for the Release Configuration
###################################################

# Set the optimization level
#RISCV_ASFLAGS += -O0
#RISCV_CFLAGS += -O0
#RISCV_CXXFLAGS += -O0

#RISCV_ASFLAGS += -Ofast
#RISCV_CFLAGS += -Ofast
#RISCV_CXXFLAGS += -Ofast

RISCV_ASFLAGS += -Os
RISCV_CFLAGS += -Os
RISCV_CXXFLAGS += -Os
