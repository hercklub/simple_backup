# Simple_backup
This app is designed to make simple back up of your files or directories and also to recover from those backups.
It is capable of doing incremental backups . 
We are using our custom binary format for saving data wich is inpired from tar but its not compatible with it.
Dont rely on back ups made by this app , after all this was just school project and may contain some bugs :) 

*Setup*
To build this project all you need is execute 'make' or 'make all'.

*Usage*

./bckuper -B -f SOURCE -o DEST -c CONFIG FILE	  
		  -R -f SOURCE [-i FILES] 
