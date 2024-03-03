## Ruthviks Car Rental System
For this assignment I implemented a Car Rental System in C++ using Object Oriented Programming and File Handling using csv files. The code is present in [main.cpp](/main.cpp). The system has 3 kinds of users as mentioned in the [problem statement](/CS253_Assignment_1.pdf) and each of them have different functionalities and specifications. All the functionalities of the statement have been implemented and I have used 3 databases as specified.
+ [`customers.csv`](/customers.csv) stores the dedtails of the customers in the  [name,id,password,customer record,dues]. The Customer record is typically assumed to be in betweeen 0 and 100, but the system also accepts higher or lower records. But a record not in this range typically means you can rent all the available cars or none of the available cars. The dues are updated whenever you return a car, this will include the addition of the base price of the car and the fine on the customer for returning the car post the due date.
+ [`employee.csv`](/employee.csv) stores the details of all employees and managers using the system. This file stores the attributes [name,id,password,employee/manager,record,dues]. The employee record has the same constraints as the customer record. The dues are updated whenever you return a car, this will include the addition of the base price of the car and the fine on the user for returning the car post the due date.
+ [`cars.csv`](/cars.csv) stores [model,id,condition,availability,date_rented,rented_by_user_type,id_of_issuer,min_record,base_price]. The condition of the car is an integer on the scale of 0 and 5, where 0 indicates that the car is in an excellent condition whereas 5 indicates that the car is highly damaged. The availability of the car is 1 when not available whereas it is 0 when it is available. The following 3 columns are nil if the car is available else the column date_rented, stores the date on which the car was rented, the column rented_by_user_type stores who rented the car i.e. customer/employee/manager and id_of_isssuer stores the id of the user who rented the specific car, the column min_record is the minimum record needed by a user to rent the car and the base_price of the car is the price levied on all users for renting a car which is added to the dues.

To run the system, type the following commands in the console:
``` 
g++ main.cpp -o main.exe
.\main.exe
```
The system will run on the console. The data modified throughout the program run will be reflected in the csv files.<br>
# Functionality
* All the fields of the Customer, Employee and the Manager are case sensitive, further there cannot exist 2 users with the same ID and 2 cars with the same ID.
* A new account can be made by the user only if he is a Customer, if he is an Employee or Manager, an existing manager should add them to the system.
* A new customer during registration gets a default customer value of 70 and dues as 0.
* Any User can rent a max of 3 cars at any time.
* While returning a car, a fine of 50 per day from the due date is imposed and this is added along with the base price to the dues of the user. If the user is an employee he gets an additional 15% discount.
* The record of either customer or user is reduced by twice the number of days of delayed return and the condition in which it is returned in reference to how it was rented multiplied by a factor of 5, which will be manually verified by the manager.<br>
These are the underlying assumptions of the system, the other functionalities are as mentioned in the problem statement and evident during the execution of the program.
