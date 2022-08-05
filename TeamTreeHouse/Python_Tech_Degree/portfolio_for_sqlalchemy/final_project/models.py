from flask import Flask
from flask_sqlalchemy import SQLAlchemy
import datetime


app = Flask(__name__)
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///projects.db'
db = SQLAlchemy(app)


class Projects(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    title = db.Column('Title', db.String())
    date = db.Column('Date', db.String())
    description = db.Column('Description', db.String())
    skills = db.Column('skills practiced', db.String())
    url = db.Column('url', db.String())
    
    def __repr__(self):
        print(self.id, self.title, self.date,
             self.description, self.skills, self.url)