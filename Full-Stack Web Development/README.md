# Full-Stack Web Development (Titile: Fablix)

## Description

This is full-stack web development project, called Fablix. As it can be noticed from the name, it is movie related web. User can login, logout, search, browse, add item to cart, purchase movies. It does not support streaming movies. All required data is stroed in the SQL, wihch is conceptually bottom most layer of full stack, including from user info to movie info, and the user interface is implemented by HTML. Each element and layer will be explained through the document. Since it is complicated and contains a lot of details, It will constantly updated.

## Requirements for Each Layer

### Database - MySQL (Bottom Layer)

For implementing database, it will use MySQL. The all information and attribute of required tables are listed in [create_table.sql](<create_table.sql>), [movie-data.sql](<movie-data.sql>) and [create_employee_table.sql](<create_employee_table.sql>). Also, for increase performance, it supports full text search, which is listed in [FullText.sql](<FullText.sql>). Also, it helps fuzzy search and auto complete. Auto complete is done by full text search and built-in library in python, and fuzzy search is done by [ed.c](<ed.c>). Another tool that is used for inprove performance is stored procedure. It is listed in [stored-procedure.sql](<stored-procedure.sql>).

### Web Server - Tomcat (Middle Layer)

For this project, Tomcat is used as web server.

### Front Display (Browser) - HTML / Ajax (Top Layer)

There is not too much deatil on front end work for this project, but HTML and Ajax is used for front work and connection between Tomcat and browser.

### Expanding - Amazon AWS, Google GCP, Docker, Kubernetes

The listed tool are used to improve performance and the expanding of web server.

### Security - reCAPTCHA, HTTPS

The listed tool are used to achieve security of web server. Also, encrypted password in MySQL is used as well.

### Stress test - JMeter

To do the stress test and check the performance, Jmeter is used for this project.
