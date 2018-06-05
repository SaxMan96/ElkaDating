create table User(
	ID INTEGER PRIMARY KEY AUTOINCREMENT,
  email varchar(70),
  name varchar(50),
  surname varchar(100),
	password varchar(50),
	active varchar(1),
	isLecturer varchar(1),
	isAdmin varchar(1)
);

create table Message(
        ID INTEGER PRIMARY KEY AUTOINCREMENT,
	userID INTEGER NOT NULL,
        data BLOB,
	FOREIGN KEY(userID) REFERENCES User(ID)
);

create table Event(
        ID INTEGER PRIMARY KEY AUTOINCREMENT,
	userID INTEGER NOT NULL,
	lecturerID INTEGER,
        accepted varchar(1),
        teacherEvent varchar(1),
	name TEXT,
  	description TEXT,
  	startTime varchar(12),
  	endTime varchar(12),
        FOREIGN KEY(userID) REFERENCES User(ID),
  	FOREIGN KEY(lecturerID) REFERENCES User(ID)
);