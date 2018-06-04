create table User(
	ID INTEGER PRIMARY KEY AUTOINCREMENT,
	email varchar(30),
	password varchar(50),
	active varchar(1),
	isLecturer varchar(1),
	isAdmin varchar(1)
);

create table Message(
	ID INTEGER NOT NULL,
	userID INTEGER NOT NULL,
	data BLOB,
	PRIMARY KEY(ID, userID),
	FOREIGN KEY(userID) REFERENCES User(ID)
);

create table Event(
	ID INTEGER NOT NULL,
	userID INTEGER NOT NULL,
	lecturerID INTEGER,
	name TEXT,
  	description TEXT,
  	startTime varchar(12),
  	endTime varchar(12),
	PRIMARY KEY(ID, userID),
  	FOREIGN KEY(userID) REFERENCES User(ID),
  	FOREIGN KEY(lecturerID) REFERENCES User(ID)
);

