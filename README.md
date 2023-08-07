# Fcd - :zap: Fast Change Dir

Quick and simple way to find and change directories in your shell

## Demo

![Demo Gif](./assets/demo.gif)

## Installation

Install the git repository and compile the project
<br /> 
You can also remove the folder after installation

```bash
git clone https://github.com/jmattaa/fcd
cd fcd/
sudo make install
```

To use the fcd command you need to alias it in your shell config

### Bash:
Go into your .bashrc file and alias fcd like this
```bash 
alias fcd="source ~/.fcd/fcd"
```

### Zsh:
Go into your .zshrc file and alias zsh like this
```bash
alias fcd="source ~/.fcd/fcd"
```

### Fish:
In your fish configuration folder go to config.fish and alias it like this
```bash
alias fcd="source ~/.fcd/fcd"
```

Just alias the command in your shell config


## Usage 
Now you can run the `fcd`
<br />
It will show you all the folders and subfolders that exist in your `Home` directory
<br />
Start typing and it will search for the folders containing your search term
<br />
Select your directory by moving using the up :arrow_up: and down :arrow_down: keys
<br />
cd into that directory by pressing the enter key

## Authors

- [@jmattaa](https://www.github.com/jmattaa)


