apt-get install sqlite libsqlite3-dev
touch server_database.db
sqlite3 server_database.db < database.sql
