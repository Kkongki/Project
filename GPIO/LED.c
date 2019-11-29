#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main_menu(void);

int main( int argc, char **argv )
{
    system("sudo echo 298 > /sys/class/gpio/export");
    system("sudo echo 396 > /sys/class/gpio/export");
    system("sudo echo out > /sys/class/gpio/gpio298/direction");
    system("sudo echo out > /sys/class/gpio/gpio396/direction");
    
    while((key=main_menu()) != 0)
    {

        switch(key)
        {

        case '1':
            printf("No.1\n");
            system("sudo echo 0 > /sys/class/gpio/gpio298/value");
            system("sudo echo 1 > /sys/class/gpio/gpio396/value");
            break;

        case '2':
            printf("No.2\n");
            system("sudo echo 1 > /sys/class/gpio/gpio298/value");
            system("sudo echo 0 > /sys/class/gpio/gpio396/value");
            break;

        case '3':
            printf("No.3\n");
            system("sudo echo 1 > /sys/class/gpio/gpio298/value");
            system("sudo echo 1 > /sys/class/gpio/gpio396/value");
            break;

        case '4':
            printf("No.4\n");
            system("sudo echo 0 > /sys/class/gpio/gpio298/value");
            system("sudo echo 0 > /sys/class/gpio/gpio396/value");
            break;  

        case '5':
            for(int i = 0; i < 10; i++) {
                system("sudo echo 1 > /sys/class/gpio/gpio298/value");
                sleep(0.5);
                system("sudo echo 0 > /sys/class/gpio/gpio298/value");
                sleep(0.5
            break;  

        case '6':
            for(int i = 0; i < 10; i++) {
                system("sudo echo 1 > /sys/class/gpio/gpio396/value");
                sleep(0.5);
                system("sudo echo 0 > /sys/class/gpio/gpio396/value");
                sleep(0.5
            break;  

        case '7':
            for(int i = 0; i < 10; i++) {
                system("sudo echo 1 > /sys/class/gpio/gpio396/value");
                system("sudo echo 0 > /sys/class/gpio/gpio298/value");
                sleep(0.5);
                system("sudo echo 0 > /sys/class/gpio/gpio396/value");
                system("sudo echo 1 > /sys/class/gpio/gpio298/value");
                sleep(0.5
            break;
            
        case 'q':
            printf("exit\n");

            exit(0);
            break;

        default :
            printf("Wrong key ..... try again\n");
            break;
        }
    }
    system("sudo echo 298 > /sys/class/gpio/unexport");
    system("sudo echo 396 > /sys/class/gpio/unexport");
    return 0;    
}

 
int main_menu(void)
{
    int key;

    printf("\n\n");
    printf("-------------------------------------------------\n");
    printf("                    MAIN MENU\n");
    printf("-------------------------------------------------\n");
    printf(" 1. LED A ON                       \n");
    printf(" 2. LED B ON                       \n");
    printf(" 3. LED ALL ON                       \n");
    printf(" 4. LED ALL OFF                       \n");
    printf(" 5. LED A blink                       \n");
    printf(" 6. LED B blink                      \n");
    printf(" 7. blink                            \n");

    printf("-------------------------------------------------\n");
    printf(" q. LED Control application QUIT                 \n");
    printf("-------------------------------------------------\n");
    printf("\n\n");
 
    printf("SELECT THE COMMAND NUMBER : ");

    key=getchar();
    if (key == '\n')
        ;
    else
        getchar();

    return key;
}
