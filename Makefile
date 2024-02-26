NAME = output

CC = g++
EXTENSION = cxx

CFLAGS = -Wall -Wextra -Wpedantic -O3
LDFLAGS = -lm #-lsfml-graphics -lsfml-window -lsfml-system #-fsanitize=address

OBJ_DIR = obj
SRC_DIR = src
DOC_DIR = doc
BIN_DIR = bin
INC_DIR = inc
EIGEN_DIR = eigen-3.4.0
 

SRC = $(wildcard src/*.$(EXTENSION)) $(wildcard src/**/*.$(EXTENSION)) #all .cxx files in src

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:$(SRC_DIR)/%.$(EXTENSION)=%.o)) #remplace all .cxx by .o and replace src/ by obj/ 
OBJ_FOLDERS = $(addprefix $(OBJ_DIR)/, $(dir $(SRC:$(SRC_DIR)/%=%))) #folders to create to mimic the src folder structure

INCLUDES = $(addprefix -I ,$(shell find $(INC_DIR) -type d)) #add -I before each folder in inc so that the compiler can find the headers

# -j multifil (multi threads) / ameliore la vitesse de compliation
# --no-print-directory / n'affiche pas: make[N]: Leaving directory '...'
all:
	mkdir -p $(OBJ_FOLDERS)
	@$(MAKE) -j $(BIN_DIR)/$(NAME) --no-print-directory

# permet de pouvoir comparer la derniere modification de la dep par rapport a la regle
$(BIN_DIR)/$(NAME): $(OBJ) .gitignore
	@mkdir -p $(BIN_DIR)
	$(CC) -o $@ -L $(EIGEN_DIR) $(OBJ) $(LDFLAGS)
	@echo $(NAME) : created !

# si le .c est plus recent que le .o on rentre dans la regle
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(EXTENSION)
	@mkdir -p $(OBJ_DIR)	
	$(CC) $(CFLAGS) $(INCLUDES) -I $(EIGEN_DIR) -c $< -o $@

debug: clean
	$(MAKE) LDFLAGS="$(LDFLAGS) -g" CFLAGS="$(CFLAGS) -g -D DEBUG" all --no-print-directory

fsanitize: clean
	$(MAKE) LDFLAGS="$(LDFLAGS) -g -fsanitize=address" CFLAGS="$(CFLAGS) -g" all --no-print-directory

clean: 
	@rm -rf $(OBJ_DIR)
	@rm -fr $(DOC_DIR)
	@rm -rf $(BIN_DIR)
	@rm -fr *.log
	@echo "obj, bin, doc, log deleted"

init:	
	@mkdir -p src inc
	@echo $(SRC_DIR) $(INC_DIR) : created !

doc:
	@mkdir -p doc
	@echo creation of the DoxyFile...
	echo DOXYFILE_ENCODING      = UTF-8 > $(DOC_DIR)/DoxyFile
	echo PROJECT_NAME           = "$(NAME)" >> $(DOC_DIR)/DoxyFile
	echo OUTPUT_LANGUAGE        = French >> $(DOC_DIR)/DoxyFile
	echo INPUT                  = ../src ../inc ../README.md >> $(DOC_DIR)/DoxyFile
	echo OPTIMIZE_OUTPUT_FOR_C  = YES >> $(DOC_DIR)/DoxyFile
	echo QUIET                  = YES >> $(DOC_DIR)/DoxyFile
	echo WARNINGS               = YES >> $(DOC_DIR)/DoxyFile
	echo RECURSIVE              = YES >> $(DOC_DIR)/DoxyFile
	@echo $(DOC_DIR)/DoxyFile : created !

docHtml:
	@(cd doc; doxygen DoxyFile)
	firefox ./doc/html/index.html &

re: clean all

.gitignore:
	@echo $(OBJ_DIR) > .gitignore
	@echo $(BIN_DIR) >> .gitignore
	@echo $(DOC_DIR) >> .gitignore
	@echo *.log >> .gitignore
	@echo ".gitignore created !"

.PHONY: all, clean, init, doc, docHtml, debug, fsanitize
