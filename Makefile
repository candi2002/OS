all: commit push

add:
	git add .

commit: add
	git commit -m "Update project"

push: commit
	git push origin main

pull:
	git pull origin main
