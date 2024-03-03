# Ruthviks Car Rental System
For this assignment I implemented a Car Rental System in C++ using Object Oriented Programming and File Handling using csv files. The code is present in [main.cpp](/main.cpp). The system has 3 kinds of users as mentioned in the [problem statement](/CS253_Assignment_1) and each of them have different functionalities and specifications. All the functionalities of the statement have been implemented and I have used 3 databases as specified.
+ [`customers.csv`](/customers.csv) stores the dedtails of the customers in the  [name,id,password,customer record,dues]. The Customer record is typically assumed to be in betweeen 0 and 100, but the system also accepts higher or lower records. But a record not in this range typically means you can rent all the available cars or none of the available cars. The dues are updated whenever you return a car, this will include the addition of the base price of the car and the fine on the customer for returning the car post the due date.
+ [`employee.csv`](/employee.csv) stores the details of all employees and managers using the system. This file stores the attributes [name,id,password,employee/manager,record,dues]. The employee record has the same constraints as the customer record. The dues are updated whenever you return a car, this will include the addition of the base price of the car and the fine on the user for returning the car post the due date.
+ [`cars`](/cars.csv) stores [model,id,condition,availability,date_rented,rented_by_user_type,id_of_issuer,min_record,base_price]. The condition of the car is an integer on the scale of 0 and 5, where 0 indicates that the car is in an excellent condition whereas 5 indicates that the car is highly damaged. The availability of the car is 1 when not available whereas it is 

To run the system, type the following commands in the console:
``` 
g++ main.cpp -o main.exe
.\main.exe
```
The system will run on the console. The data modified throughout the program run will be reflected in the csv files.<br>
<br>
