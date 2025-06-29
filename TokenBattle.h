#pragma once
#include "GameEngine.h"

namespace AlgorithmsProjectGroup16 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class TokenBattle : public System::Windows::Forms::Form
	{
	private: array<Button^, 2>^ buttons;
	private: GameEngine* engine;
	private: bool selectingFrom = true;//flag variable used in Cell_Click
	private: int fromRow, fromCol;
	public: String^ PlayerName;//To add the player's name
	private: System::Windows::Forms::Button^ ResetButton;
	private: System::Windows::Forms::Label^ statusLabel;//current turn label
	private: System::Windows::Forms::Button^ ExitButton;
	private: System::Windows::Forms::Timer^ computerMoveTimer;
	private: System::Windows::Forms::TableLayoutPanel^ tableBoard;
	private: System::ComponentModel::IContainer^ components;

	public:
		TokenBattle(void)
		{
			InitializeComponent();

			engine = new GameEngine();
			selectingFrom = true;
			buttons = gcnew array<Button^, 2>(5, 5); //Allocates a 5x5 array of buttons that represent the cells on the board.

			// Creates a delay for the computer's move
			computerMoveTimer = gcnew System::Windows::Forms::Timer();
			computerMoveTimer->Interval = 500; // 0.5 seconds
			computerMoveTimer->Tick += gcnew System::EventHandler(this, &TokenBattle::computerMoveTimer_Tick);
			//a loop to create the button for each cell
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 5; ++j) {
					Button^ btn = gcnew Button();
					btn->Dock = DockStyle::Fill;
					btn->Font = gcnew System::Drawing::Font("Segoe UI", 16);
					btn->BackColor = Color::White;
					btn->FlatStyle = FlatStyle::Flat;
					btn->FlatAppearance->BorderSize = 1;
					btn->FlatAppearance->BorderColor = Color::LightGray;
					btn->Tag = gcnew Point(i, j);
					btn->Click += gcnew System::EventHandler(this, &TokenBattle::Cell_Click);
					tableBoard->Controls->Add(btn, j, i);
					buttons[i, j] = btn;
				}
			}

			updateBoard();
		}

	protected:
		~TokenBattle()
		{
			if (components) {
				delete components;
			}
		}



#pragma region Windows Form Designer generated code

		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->tableBoard = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->ResetButton = (gcnew System::Windows::Forms::Button());
			   this->statusLabel = (gcnew System::Windows::Forms::Label());
			   this->computerMoveTimer = (gcnew System::Windows::Forms::Timer(this->components));
			   this->ExitButton = (gcnew System::Windows::Forms::Button());
			   this->SuspendLayout();
			   // 
			   // tableBoard
			   // 
			   this->tableBoard->ColumnCount = 5;
			   this->tableBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 20)));
			   this->tableBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 20)));
			   this->tableBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 20)));
			   this->tableBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 20)));
			   this->tableBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 20)));
			   this->tableBoard->Location = System::Drawing::Point(302, 89);
			   this->tableBoard->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			   this->tableBoard->Name = L"tableBoard";
			   this->tableBoard->RowCount = 5;
			   this->tableBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			   this->tableBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			   this->tableBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			   this->tableBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			   this->tableBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			   this->tableBoard->Size = System::Drawing::Size(792, 585);
			   this->tableBoard->TabIndex = 0;
			   // 
			   // ResetButton
			   // 
			   this->ResetButton->BackColor = System::Drawing::Color::MediumAquamarine;
			   this->ResetButton->FlatAppearance->BorderSize = 0;
			   this->ResetButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->ResetButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.9F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->ResetButton->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			   this->ResetButton->Location = System::Drawing::Point(1140, 606);
			   this->ResetButton->Name = L"ResetButton";
			   this->ResetButton->Size = System::Drawing::Size(176, 52);
			   this->ResetButton->TabIndex = 1;
			   this->ResetButton->Text = L"Reset";
			   this->ResetButton->UseVisualStyleBackColor = false;
			   this->ResetButton->Click += gcnew System::EventHandler(this, &TokenBattle::ResetButton_Click);
			   // 
			   // statusLabel
			   // 
			   this->statusLabel->AutoSize = true;
			   this->statusLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20.1F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->statusLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(192)));
			   this->statusLabel->Location = System::Drawing::Point(302, 30);
			   this->statusLabel->Name = L"statusLabel";
			   this->statusLabel->Size = System::Drawing::Size(0, 37);
			   this->statusLabel->TabIndex = 2;
			   // 
			   // ExitButton
			   // 
			   this->ExitButton->BackColor = System::Drawing::Color::Firebrick;
			   this->ExitButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->ExitButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.9F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->ExitButton->ForeColor = System::Drawing::Color::Black;
			   this->ExitButton->Location = System::Drawing::Point(1140, 675);
			   this->ExitButton->Name = L"ExitButton";
			   this->ExitButton->Size = System::Drawing::Size(176, 52);
			   this->ExitButton->TabIndex = 2;
			   this->ExitButton->Text = L"Exit";
			   this->ExitButton->UseVisualStyleBackColor = false;
			   this->ExitButton->Click += gcnew System::EventHandler(this, &TokenBattle::ExitButton_Click);
			   // 
			   // TokenBattle
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(9, 21);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::Black;
			   this->ClientSize = System::Drawing::Size(1370, 749);
			   this->Controls->Add(this->statusLabel);
			   this->Controls->Add(this->ResetButton);
			   this->Controls->Add(this->tableBoard);
			   this->Controls->Add(this->ExitButton);
			   this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			   this->MaximizeBox = false;
			   this->Name = L"TokenBattle";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"Token Battle - X vs Y";
			   this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			   this->Load += gcnew System::EventHandler(this, &TokenBattle::TokenBattle_Load);
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }

#pragma endregion
	public:void UpdatePlayerName() {
		statusLabel->Text = "Current turn: " + PlayerName;
	}
	private: System::Void Cell_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ btn = safe_cast<Button^>(sender);//refers to the button clicked
		Point pos = safe_cast<Point>(btn->Tag);//the position of the clicked cell
		int row = pos.X;
		int col = pos.Y;

		if (selectingFrom) {//if true then the player is selecting the "from" button if false then the player is selecting the "to" button
			if (engine->getCell(row, col) == PLAYER_X) {//check if the cell represents one of the tokens of the player
				fromRow = row;
				fromCol = col;
				selectingFrom = false;//set the flag to false,meaning that the player will choose the destination cell now

				// Highlight selected cell
				btn->BackColor = Color::LightBlue;//change the cell color to light blue to indicate that it's selected
			}
		}
		else {
			if (engine->isValidMove(fromRow, fromCol, row, col)) {//check if it's a valid move according to the game rules
				engine->applyMove(fromRow, fromCol, row, col);//if yes apply the move
				selectingFrom = true;//set the flag to true,meaning the player can choose a new token to move

				// Reset all button colors after a move 
				for (int i = 0; i < 5; ++i) {
					for (int j = 0; j < 5; ++j) {
						buttons[i, j]->BackColor = SystemColors::Control;
					}
				}
				processTurn();//call the function to process the turn of the next player
			}
			else {
				MessageBox::Show("Invalid move!");
				selectingFrom = true;//start the selection of the token after the move was invalid
			}
		}
	}

	//responsible for handling the design of the game board
	private: void updateBoard() {
		System::Drawing::Size imgSize(80, 80);

		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				buttons[i, j]->BackColor = Color::White;
				buttons[i, j]->Image = nullptr;
				buttons[i, j]->Text = "";

			

				if ((i == 0 && j == 0) || (i == 0 && j == 4) || (i == 4 && j == 0) || (i == 4 && j == 4)) {
					buttons[i, j]->BackColor = Color::Black;
					buttons[i, j]->FlatAppearance->BorderSize = 0;
				}

				char val = engine->getCell(i, j);//a variable to store which token is placed in this current cell
				if (val == PLAYER_X) {
					String^ pathX = Application::StartupPath + "\\tokenX.png";
					Image^ imgX = Image::FromFile(pathX);
					buttons[i, j]->Image = gcnew Bitmap(imgX, imgSize);
					buttons[i, j]->ImageAlign = ContentAlignment::MiddleCenter;
				}
				else if (val == PLAYER_Y) {
					String^ pathY = Application::StartupPath + "\\tokenY.png";
					Image^ imgY = Image::FromFile(pathY);
					buttons[i, j]->Image = gcnew Bitmap(imgY, imgSize);
					buttons[i, j]->ImageAlign = ContentAlignment::MiddleCenter;
				}
			}
		}
	}

	private: void resetGame() {
		engine = new GameEngine();//create a new instance of GameEngine
		selectingFrom = true;//set the flag to true
		fromRow = fromCol = -1;//set the values for the fromRow and the fromColumn to -1 indicating no cell is selected yet
		updateBoard();//update the board to its reset state
		statusLabel->Text = "Current Turn: " + PlayerName;//Start the game with the user player
	}

	private: System::Void computerMoveTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
		computerMoveTimer->Stop(); // Stop the timer
		engine->computerMove();    // Make the AI move
		processTurn();       // Continue processing
	}
	
	private: void processTurn() {
		updateBoard();//update the board with the new changes
		statusLabel->Text = "Current Turn: " + ((engine->currentPlayer == PLAYER_X) ? PlayerName : "Computer");//update the current turn
		//check if the user has won
		if (engine->isWinningState(PLAYER_X)) {
			MessageBox::Show(PlayerName + " wins!");
			resetGame();
			return;
		}
		//check if the computer has won
		if (engine->isWinningState(PLAYER_Y)) {
			MessageBox::Show("Computer wins!");
			resetGame();
			return;
		}
		//check if the current player has no valid moves
		if (!engine->hasValidMoves(engine->currentPlayer)) {
			if (engine->currentPlayer == PLAYER_X)//if it's the user skip his turn
				MessageBox::Show(PlayerName + " has no valid moves. Turn skipped.");
			else//if it's the computer skip its turn
				MessageBox::Show("Computer has no valid moves. Turn skipped.");

			engine->currentPlayer = (engine->currentPlayer == PLAYER_X) ? PLAYER_Y : PLAYER_X;//skipping the tun
			processTurn(); // Continue processing with the next player
			return;
		}
		if (engine->currentPlayer == PLAYER_Y) {
			statusLabel->Text = "Computer is thinking...";
			// Start the timer for Player Y's move
			computerMoveTimer->Start();//start the delay time of the computer
			return;
		}
	}

	private: System::Void ResetButton_Click(System::Object^ sender, System::EventArgs^ e) {
		resetGame();//resets the game

	}
	 private: System::Void ExitButton_Click(System::Object^ sender, System::EventArgs^ e) {
			
		 this->Close(); // Close the game		   
	}

#pragma endregion
	private: System::Void TokenBattle_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
