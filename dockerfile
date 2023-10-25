# Commencer avec une image Ubuntu
FROM ubuntu:latest

# Mettre à jour le système
RUN apt-get update && apt-get upgrade -y

# Installer les outils de développement couramment utilisés
RUN apt-get install -y build-essential gdb valgrind git vim libreadline-dev 
# zsh

# Installe Oh My Zsh
#  sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# Configure Zsh comme shell par défaut
#  echo "exec zsh" >> ~/.bashrc

# Définit Zsh comme shell par défaut
SHELL ["/bin/zsh", "-c"]

# Installer X11 et les dépendances de la minilibx
# RUN apt-get install -y xorg libxext-dev zlib1g-dev libbsd-dev 

# Définir le répertoire de travail
WORKDIR /workspace

COPY . /workspace

RUN  ["make", "re"]