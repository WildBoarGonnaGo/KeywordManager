#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	QMap<QString, QVariant> map;
	map["First Name"] = "Misha";
	map["Second Name"] = "Zavelskiy";

	MVCTestWidget w(map);

	w.show();
	return app.exec();
}
