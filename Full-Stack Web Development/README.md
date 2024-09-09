# Full-Stack Web Development (Titile: Fablix)

## Description

This is full-stack web development project, called Fablix. As it can be noticed from the name, it is movie related web. User can login, logout, search, browse, add item to cart, purchase movies. It does not support streaming movies. All required data is stroed in the SQL, wihch is conceptually bottom most layer of full stack, including from user info to movie info, and the user interface is implemented by HTML. Each element and layer will be explained through the document. Since it is complicated and contains a lot of details, It will constantly updated.

## Requirements for Each Layer

### Database - MySQL (Bottom)

For implementing database, it will use MySQL. The all information and attribute of required tables are listed in [create_table.sql](<create_table.sql>), [movie-data.sql](<movie-data.sql>) and [create_employee_table.sql](<create_employee_table.sql>). Also, for increase performance, it supports full text search, which is listed in [FullText.sql](<FullText.sql>).
