.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
CD = cd ..
TAR = tar -zcvf
######################################
# Project Name (generate executable with this name)
TARGET = cs296_base
#debug_target = bin/cs296_base
#release_target = bin/cs296_base


# Project Paths
PROJECT_ROOT=$(HOME)/cs296_base_code
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/obj
BINDIR = $(PROJECT_ROOT)/bin
DOCDIR = $(PROJECT_ROOT)/doc
SCRIPTDIR = $(PROJECT_ROOT)/scripts
PLOTSDIR = $(PROJECT_ROOT)/plots

SRCDIRNON = $(PROJECT_ROOT)/src_non
OBJDIRNON1 = $(PROJECT_ROOT)/obj_non1
OBJDIRNON2 = $(PROJECT_ROOT)/obj_non2

BOX2DDIR = $(PROJECT_ROOT)/external/src/Box2D

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-g -O3 -Wall 
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib
OPTFLAGS = -O3
PRFLAGS = -pg

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

SRCSNON := $(wildcard $(SRCDIRNON)/*.cpp)
OBJSNON1 := $(SRCSNON:$(SRCDIRNON)/%.cpp=$(OBJDIRNON1)/%.o)
OBJSNON2 := $(SRCSNON:$(SRCDIRNON)/%.cpp=$(OBJDIRNON2)/%.o)



.PHONY: exe setup doc clean distclean

all: setup exe doc

################################################# SIMULATION PART ###############################################################
exe: setup $(BOX2DDIR) $(BINDIR)/$(TARGET)

$(BOX2DDIR):
	@chmod 744 scripts/extract.sh 
	@./scripts/extract.sh

setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p obj
	@mkdir -p bin

$(BINDIR)/$(TARGET): $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

################################################## NONSIMULATION PART ###############################################################

setup_non:
	@mkdir -p obj_non1
	@mkdir -p obj_non2
	@mkdir -p bin
	@mkdir -p data
	@mkdir -p plots_non1
	@mkdir -p plots_non2
	
################### debug version ######################

debug_extract: 
	@chmod 744 scripts/debug_extract.sh
	@./scripts/debug_extract.sh

debug_prof: debug_target
	@chmod 744 scripts/profile.sh
	@./scripts/profile.sh
	
debug_target: $(OBJSNON1)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) $(PRFLAGS) -o bin/cs296_base $(LDFLAGS) $(OBJSNON1) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include $(OBJSNON1:.o=.d)

$(OBJSNON1): $(OBJDIRNON1)/%.o : $(SRCDIRNON)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(PRFLAGS) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

debug_report: $(SCRIPTDIR)/g10_gen_csv.py $(SCRIPTDIR)/g10_gen_plots_debug.py
	@python3 scripts/g10_gen_csv.py
	@python3 scripts/g10_gen_plots_debug.py
	
debug: setup_non debug_extract debug_target debug_prof debug_report
	
#################### release version ######################

release_extract:
	@chmod 744 scripts/release_extract.sh
	@./scripts/release_extract.sh
	
release_prof: release_target
	@chmod 744 scripts/release_profile.sh
	@./scripts/release_profile.sh
	
release_target: $(OBJSNON2)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) $(PRFLAGS) $(OPTFLAGS) -o bin/cs296_base $(LDFLAGS) $(OBJSNON2) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err 

-include $(OBJSNON2:.o=.d)

$(OBJSNON2): $(OBJDIRNON2)/%.o : $(SRCDIRNON)/%.cpp
	@$(CC) $(PRFLAGS) $(OPTFLAGS) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

release_report: $(SCRIPTDIR)/g10_gen_csv.py $(SCRIPTDIR)/g10_gen_plots_release.py
	@python3 scripts/g10_gen_csv.py
	@python3 scripts/g10_gen_plots_release.py

release: setup_non release_extract release_target release_prof release_report

##################################################################################################################################


doc: $(DOCDIR)/g10_prof_report.tex $(DOCDIR)/Doxyfile
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@./scripts/convert.sh
	@python3 scripts/g10_gen_html.py
	@latex $(DOCDIR)/g10_prof_report.tex
	@bibtex g10_prof_report.aux
	@latex $(DOCDIR)/g10_prof_report.tex
	@latex $(DOCDIR)/g10_prof_report.tex
	@latex $(DOCDIR)/g10_prof_report.tex
	@latex $(DOCDIR)/g10_prof_report.tex
	@dvips g10_prof_report.dvi
	@ps2pdf g10_prof_report.ps $(DOCDIR)/g10_prof_report.pdf
	@rm *.aux *.blg *.bbl *.dvi *.log *.ps  
	

dist: distclean
	@$(RM) -rf $(OBJDIR) $(OBJDIRNON1) $(OBJDIRNON2) $(BINDIR) $(DOCDIR)/html data plots_non1 plots_non2 gmon.out install $(DOCDIR)/*.pdf
	@$(CD) ;\
	tar -zcvf cs296_base_code.tar.gz cs296_base_code ;\
	
install: exe doc
	@cd .. ;\
	mkdir -p install ;\
	cp -r cs296_base_code/bin install/ ;\
	cp -r cs296_base_code/doc install/ ;\
	cp -r cs296_base_code/scripts install/ ;\
	cp -r cs296_base_code/Makefile install/ ;\

clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~ $(OBJDIRNON1) $(OBJDIRNON2)
	@$(ECHO) "Done"

distclean: clean
	@$(RM) -rf $(OBJDIR) $(OBJDIRNON1) $(OBJDIRNON2) $(BINDIR) $(DOCDIR)/html data plots_non1 plots_non2 gmon.out install $(DOCDIR)/*.pdf *.~ *.dvi *.aux $(DOCDIR)/*.bbl $(DOCDIR)/*.blg $(DOCDIR)/*.dvi $(DOCDIR)/*.log $(DOCDIR)/*.aux plots_doc/*.eps $(DOCDIR)/*.html
