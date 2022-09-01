#include "Qt2048.h"

using _2048Game::SIDE_LENGTH;
using std::vector, std::to_string;


Qt2048::Qt2048() :
	interfaceGrid_(new QGridLayout()) 
{
	QWidget* mainWidget = new QWidget(this);
	mainWidget->setStyleSheet("background-color: #ECF0F1");
	mainWidget->setLayout(interfaceGrid_);
	setCentralWidget(mainWidget);


	for (int i = 0; i < SIDE_LENGTH; ++i) {
		for (int j = 0; j < SIDE_LENGTH; ++j) {
			QPushButton* newSquare = new QPushButton(this);
			newSquare->setFixedSize(QSize(100, 100));
			squares_.push_back(newSquare);
			interfaceGrid_->addWidget(newSquare, i, j, Qt::AlignCenter);
		}
	}

	connect(this, SIGNAL(startGame()), Grid::getInstance(), 
		SLOT(generateStartValues()), Qt::UniqueConnection);
	connect(Grid::getInstance(), SIGNAL(contentHasChanged(const std::vector<Square>&)),
		this, SLOT(changeContent(const std::vector<Square>&)), Qt::UniqueConnection);

	emit startGame();
}


void Qt2048::changeContent(const vector<Square>& gridContent) {
	int i = 0;

	for (const Square& square : gridContent) {
		squares_[i++]->setText(QString::number(square.getValue()));
	}
}