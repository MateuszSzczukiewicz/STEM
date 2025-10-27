#!/bin/bash

set -e

TASK_NAME="$1"

if [ -z "$TASK_NAME" ]; then
    echo "Error: You must provide a task name."
    echo "Example: ./scripts/generate_report.sh combinatorics_urn_sampling"
    exit 1
fi

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
TASK_DIR="$PROJECT_ROOT/tasks/$TASK_NAME"

if [ ! -d "$TASK_DIR" ]; then
    echo "Error: Task directory $TASK_DIR does not exist."
    exit 1
fi

if [ ! -f "$TASK_DIR/report.Rmd" ]; then
    echo "Error: report.Rmd not found in $TASK_DIR"
    exit 1
fi

echo "Generating report for task: $TASK_NAME"
cd "$TASK_DIR"
R -e "rmarkdown::render('report.Rmd')"

echo "✅ Report generated successfully!"
echo "   PDF: $TASK_DIR/report.pdf"
echo "   HTML: $TASK_DIR/report.html"
