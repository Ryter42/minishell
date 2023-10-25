# Commencer avec une image Ubuntu
FROM ubuntu:latest

# Mettre à jour le système
RUN apt-get update && apt-get upgrade -y

# Installer les outils de développement couramment utilisés
RUN apt-get install -y build-essential gdb valgrind git vim libreadline-dev

# Installer X11 et les dépendances de la minilibx
RUN apt-get install -y xorg libxext-dev zlib1g-dev libbsd-dev 

# Définir le répertoire de travail
WORKDIR /workspace

COPY . /workspace