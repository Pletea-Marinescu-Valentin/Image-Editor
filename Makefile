build:image_editor
image_editor:image_editor.c
	gcc image_editor.c load.c utils.c select.c rotate.c crop.c apply.c save.c equalize.c -o image_editor -lm
clean:
	rm image_editor
