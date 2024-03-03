TOTAL_FILES := $(shell echo $(words $(SRCS) $(GNL_SRC) $(FT_PRINTF_SRC) $(LIBFT_SRC)))
CURRENT_FILE = 1

define progress
    @printf "$(GENERATE) $(YELLOW)Generating $(NAME) object files: %3d%% (%d/%d)$(RESET)\r" $$(($(CURRENT_FILE)*100/$(TOTAL_FILES))) $(CURRENT_FILE) $(TOTAL_FILES)
    @$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
    # @if [ $(CURRENT_FILE) -gt $(TOTAL_FILES) ]; then \
    #     printf "$(GENERATE) $(YELLOW)Generated $(NAME) object files!%-50.50s\n$(RESET)"; \
    # fi
endef