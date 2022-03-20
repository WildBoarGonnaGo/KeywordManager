#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	QMap<QString, QVariant> map;
	map["First Name"] = "Misha";
	map["Second Name"] = "Zavelskiy";
    map["Age"] = 32;

    QList<KeywordDataSet> list;

    MVCTestWidget w(map, std::move(list));

	w.show();
	return app.exec();
}
