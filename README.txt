*******************************************************************************************
This program broadcasts some of your system information in the local network via udp socket                             
-------------------------------------------------------------------------------------------
Author : Sami Natshe                                                                                                    
Email :  sami.natshe@gmail.com|                                                                                         
-------------------------------------------------------------------------------------------
in order to run this program please do the following steps:                                                              
1- creat a new folder on you desktop                                                                                    
2- download the files [server.c client.c funcs.c funcs.h Makefile ]                                                     
3- open a terminal and run Makefile in the command line  $./make                                                        
4- run the server  $./server                                                                                            
5- open a new terminal and run the client $./client                                                                     
 -after running both client and server you will start seeing your system information appear
 on the server screen ," notice that the data in JSON format".      
 -notice that you need to close the port if you run the server more than one time , use the 
 command  $fuser -k 8021/udp. 
*******************************************************************************************
enjoy!
