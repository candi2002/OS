all: commit push

add:
	git add .

commit: add
	git commit -m "Update project"

push:
	git push origin main

pull:
	git pull origin main
