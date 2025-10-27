.PHONY: all build clean test reports help install-r-deps

BUILD_DIR := build
TASKS_DIR := tasks

all: build

help:
	@echo "Statistics and Probability - Build System"
	@echo ""
	@echo "Available targets:"
	@echo "  make build          - Build all C++ executables"
	@echo "  make test           - Run all unit tests"
	@echo "  make reports        - Generate all R Markdown reports (PDF + HTML)"
	@echo "  make report TASK=<name> - Generate report for specific task"
	@echo "  make clean          - Remove build artifacts"
	@echo "  make install-r-deps - Install required R packages"
	@echo "  make all            - Build everything (default)"
	@echo ""
	@echo "Example:"
	@echo "  make build"
	@echo "  make report TASK=combinatorics_urn_sampling"
	@echo "  make reports"

build:
	@echo "Building C++ project..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. && $(MAKE)
	@ln -sf $(BUILD_DIR)/compile_commands.json compile_commands.json
	@echo "Build complete!"

test: build
	@echo "Running tests..."
	@cd $(BUILD_DIR) && ctest --output-on-failure

clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)
	@rm -f compile_commands.json
	@find $(TASKS_DIR) -name "*.pdf" -o -name "*.html" -o -name "*.csv" -o -name "*.dat" | xargs rm -f
	@echo "Clean complete!"

install-r-deps:
	@echo "Installing R dependencies to user library..."
	@R -e "dir.create(Sys.getenv('R_LIBS_USER'), recursive=TRUE, showWarnings=FALSE); .libPaths(Sys.getenv('R_LIBS_USER')); install.packages(c('ggplot2', 'readr', 'glue', 'rmarkdown', 'knitr', 'scales'), repos='https://cloud.r-project.org', lib=Sys.getenv('R_LIBS_USER'))"
	@R -e "if (!requireNamespace('tinytex', quietly=TRUE)) { install.packages('tinytex', repos='https://cloud.r-project.org', lib=Sys.getenv('R_LIBS_USER')); tinytex::install_tinytex() }"
	@echo "R dependencies installed!"

report: build
ifndef TASK
	@echo "Error: TASK variable not set"
	@echo "Usage: make report TASK=combinatorics_urn_sampling"
	@exit 1
endif
	@echo "Generating report for task: $(TASK)..."
	@cd $(TASKS_DIR)/$(TASK) && R -e "rmarkdown::render('report.Rmd')"
	@echo "Report generated: $(TASKS_DIR)/$(TASK)/report.pdf"
	@echo "Report generated: $(TASKS_DIR)/$(TASK)/report.html"

reports: build
	@echo "Generating all reports..."
	@for task_dir in $(TASKS_DIR)/*/; do \
		if [ -f "$$task_dir/report.Rmd" ]; then \
			task_name=$$(basename $$task_dir); \
			echo "Processing: $$task_name"; \
			cd $$task_dir && R -e "rmarkdown::render('report.Rmd')" && cd ../..; \
		fi \
	done
	@echo "All reports generated!"
