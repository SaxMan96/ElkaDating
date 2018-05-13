reate table User(
	ID INTEGER PRIMARY KEY AUTOINCREMENT,
	email varchar(30),
	password varchar(50),
	active varchar(1),
	isLecturer varchar(1),
	isAdmin varchar(1)
);

create table Message(
	ID INTEGER,
	userID INTEGER,
	data BLOB,
	FOREGIN KEY(userID) REFERENCES User(ID),
	PRIMARY KEY(ID, userID)
);

create Event(
	ID INTEGER PRIMARY KEY AUTOINCREMENT,
	userID INTEGER,
	lecturerID INTEGER,
	name TEXT,
  description TEXT,
  startTime varchar(12),
  endTime varchar(12),
  FOREGIN KEY(userID) REFERENCES User(ID),
  FOREGIN KEY(lecturerID) REFERENCES User(ID),
	PRIMARY KEY(ID, userID)
);

