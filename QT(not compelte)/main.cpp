#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create the login window
    QWidget login;
    login.setWindowTitle("Login");

    // Create the username label and input field
    QLabel username_label("Username:", &login);
    QLineEdit username_input(&login);

    // Create the password label and input field
    QLabel password_label("Password:", &login);
    QLineEdit password_input(&login);
    password_input.setEchoMode(QLineEdit::Password);

    // Create the login button
    QPushButton login_button("Login", &login);

    // Set the layout of the login window
    QVBoxLayout layout(&login);
    layout.addWidget(&username_label);
    layout.addWidget(&username_input);
    layout.addWidget(&password_label);
    layout.addWidget(&password_input);
    layout.addWidget(&login_button);

    // Create the course selection window
    QWidget course_selection;
    course_selection.setWindowTitle("Course Selection");

    // Create the course selection labels
    QLabel course_label_1("1. AdvanceProgramming", &course_selection);
    QLabel course_label_2("2. Math ", &course_selection);
    QLabel course_label_3("3. Physics", &course_selection);
    QLabel course_label_4("4. Workshop", &course_selection);
    QLabel course_label_5("5. differntial", &course_selection);

    // Set the layout of the course selection window
    QVBoxLayout course_layout(&course_selection);
    course_layout.addWidget(&course_label_1);
    course_layout.addWidget(&course_label_2);
    course_layout.addWidget(&course_label_3);
    course_layout.addWidget(&course_label_4);
    course_layout.addWidget(&course_label_5);

    // Hide the course selection window by default
    course_selection.hide();

    // Connect the login button to the course selection window
    QObject::connect(&login_button, &QPushButton::clicked, [&]() {
        if (username_input.text() == "my_username" && password_input.text() == "my_password") {
            login.hide();
            course_selection.show();
        }
    });

    // Show the login window
    login.show();

    return app.exec();
}
