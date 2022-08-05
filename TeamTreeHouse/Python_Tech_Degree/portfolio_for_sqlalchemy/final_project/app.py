from datetime import datetime
from time import strptime
from flask import (render_template, session,
                 url_for, request, redirect, send_file)
from models import db, Projects, app
import os


@app.route('/')
def index():
    projects = Projects.query.all()
    return render_template("index.html", projects=projects)


@app.route('/about')
def about():
    projects = Projects.query.all()
    return render_template('about.html', projects=projects)


@app.route('/projects/<id>')
def projects_id(id):
    projects = Projects.query.all()
    current_project = Projects.query.get_or_404(id)
    skills = current_project.skills.split(',')
    date = datetime.strptime(current_project.date, "%Y-%m")
    return render_template('detail.html', project=current_project,
                             projects=projects, skills=skills, date=date)


@app.route('/projects/add', methods=['GET', 'POST'])
def add_project():
    projects = Projects.query.all()
    if request.form:
        print(request.form)
        new_project = Projects(
                        title=request.form['title'], date=request.form['date'],
                        description=request.form['desc'], skills=request.form['skills'],
                        url=request.form['github'])
        db.session.add(new_project)
        db.session.commit()
        return redirect(url_for('index'))
    return render_template('projectform.html', projects=projects)


@app.route('/projects/<id>/edit', methods=['GET', 'POST'])
def edit(id):
    projects = Projects.query.all()
    project = Projects.query.get_or_404(id)
    if request.form:
        project.title = request.form['title']
        project.date = request.form['date']
        project.description = request.form['desc']
        project.skills = request.form['skills']
        project.url = request.form['github']
        db.session.commit()
        return redirect(url_for('index'))
    return render_template('edit.html', projects=projects, project=project)


@app.route('/projects/<id>/delete')
def delete(id):
        project = Projects.query.get_or_404(id)
        db.session.delete(project)
        db.session.commit()
        return redirect(url_for('index'))


@app.route('/download')
def download_file():
    p = "static/downloads/sullivan_andison_resume.pdf"
    return send_file(p,as_attachment=True)

  
@app.errorhandler(404)
def not_found(error):
    projects = Projects.query.all()
    return render_template('404.html', msg=error, projects=projects), 404


if __name__ == '__main__':
    db.create_all()
    app.run(debug=True, port=8000, host='127.0.0.1')