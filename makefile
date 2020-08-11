# ----------------------------
# Set NAME to the program name
# Set ICON to the png icon file name
# Set DESCRIPTION to display within a compatible shell
# Set COMPRESSED to "YES" to create a compressed program
# ----------------------------

NAME        ?= TETRIS
COMPRESSED  ?= NO
ICON        ?= icon.png
DESCRIPTION ?= "Tetris"

# ----------------------------
# Other Options (Advanced)
# ----------------------------

#EXTRA_CFLAGS        ?=
#USE_FLASH_FUNCTIONS ?= YES|NO
#OUTPUT_MAP          ?= YES|NO
#ARCHIVED            ?= YES|NO
#OPT_MODE            ?= -optsize|-optspeed
#SRCDIR              ?= src
#OBJDIR              ?= obj
#BINDIR              ?= bin
#GFXDIR              ?= src/gfx
#V                   ?= 1

FONTDIR ?= $(SRCDIR)/fonts

include $(CEDEV)/include/.makefile

$(OBJDIR)/fonts/fonts.src: $(FONTDIR)/testfont.inc

$(FONTDIR)/testfont.inc: $(FONTDIR)/testfont.fnt
	$(call MKDIR,$(@D))
	convfont -o carray -f $^ -a 1 -b 1 -w bold -c 2 -x 9 -l 0x0B -Z $@