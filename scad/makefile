THIS_FILE := $(lastword $(MAKEFILE_LIST))
# explicit wildcard expansion suppresses errors when no files are found

# directories
STL=stl
IMG=img
GCODE=gcode
DEPS=build

# executables
OPENSCAD=openscad-nightly
SLICER=slicer

# config
SLICER_CONFIG=conf/0.2mm_PET_MK3.ini

include $(wildcard $(DEPS)/*.deps)

.PHONY: all stl gcode png clean %.stl %.png %.gcode

all: gcode

stl: $(patsubst %.scad, $(stl)/%.stl, $(wildcard *.scad))

png: $(patsubst %.scad, $(img)/%.png, $(wildcard *.scad))

gcode: $(patsubst %.scad, $(GCODE)/%.gcode, $(wildcard *.scad))

clean:
	rm -f $(DEPS)/* $(STL)/* $(GCODE)/*

$(STL)/%.stl: %.scad
	mkdir -p $(STL)
	mkdir -p $(DEPS)
	$(OPENSCAD) -m make -o $@ -d $(DEPS)/`basename $@`.deps $<
	$(MAKE) -f $(THIS_FILE) $(IMG)/`basename $@ .stl`.png &

$(IMG)/%.png: %.scad
	mkdir -p $(IMG)
	$(OPENSCAD) -m make -o $(@:.png=-`date '+%y-%m-%d-%H-%M-%S'`.png) --imgsize=2048,2048 --render -d $(DEPS)/`basename $@`.deps $< &
	$(OPENSCAD) -m make -o $(@:.png=-`date '+%y-%m-%d-%H-%M-%S'-preview`.png) --imgsize=2048,2048 -d $(DEPS)/`basename $@`.deps $< &

$(GCODE)/%.gcode: $(STL)/%.stl
	mkdir -p $(GCODE)
	@echo $@: $<
	$(SLICER) --no-gui --load $(SLICER_CONFIG) $(shell cat ${@:$(GCODE)/%.gcode=%.slice}) -o $(GCODE)/ $< &

%.stl: $(STL)/%.stl
	@#

%.scad: $(STL)/%.stl
	@#

%.gcode: $(GCODE)/%.gcode
	@#

%.scad: $(STL)/%.stl
	@#
