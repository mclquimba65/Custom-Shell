# Simple Custom Shell
## Programmer: Mark Quimba
### Description
This program is a simple custom shell that uses Unix functions such as ```fork()``` and ```exec``` to execute process while also making sure the program does not terminate
prematurely. The program includes some custom-made functions that allows the user to perform actions that are not present in other shells. For example, typing ```history``` into 
the terminal when the program is running will display the last 10 commands typed by the user into the terminal. Furthermore, the program will output all commands typed by the user
to a hidden file called ```.shellHistory``` which then gets reset if the program is reopened. Typing ```procread``` and then the proc file the user wants to
display will display the contents of the proc file. The proc filesystem is a special filesystem in Unix-like operating systems. This means this program should be run within 
a Unix-like operating system or Virtual Machine. <br><br>
When typing:
- ```history```, the program will display the last 10 commands typed by the user.
- ```procread <procfilename>```, the program will display the contents of the desired proc file.
- ```exit```, the program will terminate safely.
- Any other unix-like command, the program will mimic the behavior of other shells using ```fork()``` and ```exec()```. <br>

### Compile Instructions and Running the Program
- A unix-like operating system is required (can be run in a virtual machine).
- ```make``` and ```gcc``` must be installed to run ```make build```.
- After running ```make build```, run ```./shell``` to run the executable for the program.
- Run ```make clean``` to clean up object files.<br>

### Resources
1. https://cplusplus.com/reference/clibrary/
2. https://pubs.opengroup.org/onlinepubs/9699919799/ (contains information about ```fork()```)
3. https://makefiletutorial.com/
4. https://docs.kernel.org/filesystems/proc.html (contains information about the proc filesystem)
5. https://www.chromium.org/chromium-os/developer-library/reference/linux-constants/errnos/
