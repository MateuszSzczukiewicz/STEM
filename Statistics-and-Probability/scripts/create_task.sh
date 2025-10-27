#!/bin/bash

TASK_SLUG=$1
TASKS_DIR="tasks"
TEMPLATE_DIR="scripts/templates"
# --------------------

if [ -z "$TASK_SLUG" ]; then
    echo "Error: You must provide a task name (slug)."
    echo "Example: ./scripts/create_task.sh bayes_coin_paradox"
    exit 1
fi

TARGET_DIR="$TASKS_DIR/$TASK_SLUG"

if [ -d "$TARGET_DIR" ]; then
    echo "Error: Directory $TARGET_DIR already exists."
    exit 1
fi

echo "Creating structure in $TARGET_DIR..."
mkdir -p "$TARGET_DIR"

cp "$TEMPLATE_DIR/analytics.cpp.tpl" "$TARGET_DIR/analytics.cpp"
cp "$TEMPLATE_DIR/simulation.cpp.tpl" "$TARGET_DIR/simulation.cpp"
cp "$TEMPLATE_DIR/report.Rmd.tpl" "$TARGET_DIR/report.Rmd"
cp "$TEMPLATE_DIR/CMakeLists.txt.tpl" "$TARGET_DIR/CMakeLists.txt"
touch "$TARGET_DIR/README.md"

sed -i "s/__TASK_SLUG__/$TASK_SLUG/g" "$TARGET_DIR/CMakeLists.txt"
sed -i "s/__TASK_SLUG__/$TASK_SLUG/g" "$TARGET_DIR/report.Rmd"

echo "add_subdirectory($TASK_SLUG)" >> "$TASKS_DIR/CMakeLists.txt"

echo "✅ Done! New task '$TASK_SLUG' has been created."
echo "   Next steps:"
echo "   1. Run 'cmake ..' in the build folder to detect the new task."
echo "   2. Fill in the logic in $TARGET_DIR/"
echo "   3. Edit $TARGET_DIR/CMakeLists.txt to link the necessary libraries from /lib."
