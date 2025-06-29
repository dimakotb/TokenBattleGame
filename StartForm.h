#pragma once
#include "TokenBattle.h"  

namespace AlgorithmsProjectGroup16 {

    using namespace System;
    using namespace System::Windows::Forms;

    public ref class StartForm : public Form
    {
    public:
        StartForm(void)
        {
            InitializeComponent();
        }

    private:
        System::Windows::Forms::Button^ btnPlay;
        System::Windows::Forms::TextBox^ nameTextBox;
        String^ PlayerName;  // Store player's name
#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(StartForm::typeid));
            this->btnPlay = (gcnew System::Windows::Forms::Button());
            this->nameTextBox = (gcnew System::Windows::Forms::TextBox());
            this->SuspendLayout();
            // 
            // btnPlay
            // 
            this->btnPlay->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
                static_cast<System::Int32>(static_cast<System::Byte>(128)));
            this->btnPlay->Font = (gcnew System::Drawing::Font(L"Ravie", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btnPlay->Location = System::Drawing::Point(502, 440);
            this->btnPlay->Name = L"btnPlay";
            this->btnPlay->Size = System::Drawing::Size(266, 78);
            this->btnPlay->TabIndex = 0;
            this->btnPlay->Text = L"Start Game";
            this->btnPlay->UseVisualStyleBackColor = false;
            this->btnPlay->Click += gcnew System::EventHandler(this, &StartForm::btnPlay_Click);
            // 
            // nameTextBox
            // 
            this->nameTextBox->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->nameTextBox->Font = (gcnew System::Drawing::Font(L"Times New Roman", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->nameTextBox->ForeColor = System::Drawing::Color::Black;
            this->nameTextBox->Location = System::Drawing::Point(526, 545);
            this->nameTextBox->Name = L"nameTextBox";
            this->nameTextBox->Size = System::Drawing::Size(212, 35);
            this->nameTextBox->TabIndex = 2;
            this->nameTextBox->Text = L"Enter your name";
            this->nameTextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            this->nameTextBox->GotFocus += gcnew System::EventHandler(this, &StartForm::nameTextBox_GotFocus);
            this->nameTextBox->LostFocus += gcnew System::EventHandler(this, &StartForm::nameTextBox_LostFocus);
            // 
            // StartForm
            // 
            this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
            this->ClientSize = System::Drawing::Size(990, 630);
            this->Controls->Add(this->nameTextBox);
            this->Controls->Add(this->btnPlay);
            this->Name = L"StartForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Ready to Play";
            this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
            this->Load += gcnew System::EventHandler(this, &StartForm::StartForm_Load);
            this->ResumeLayout(false);
            this->PerformLayout();

        }

        void btnPlay_Click(Object^ sender, EventArgs^ e)
        {
            // Store player's name and proceed to game
            this->PlayerName = nameTextBox->Text;

            if (this->PlayerName->Trim() == "Enter your name" || this->PlayerName->Trim() == "")//check if the PlayerName textbox is empty
            {
                MessageBox::Show("Please enter your name to continue.", "Name Required", MessageBoxButtons::OK, MessageBoxIcon::Warning);//a warning message box is displayed informing the user to enter his name to proceed playing
                return;//ensuring that the game doesn't start without the name
            }

            this->Hide();  // Hide the StartForm
            TokenBattle^ gameForm = gcnew TokenBattle();
            gameForm->PlayerName = this->PlayerName;//assigns the PlayerName variable in the TokenBattle form with the PlayerName taken as an input in the StartForm
            gameForm->UpdatePlayerName();//Update the Player name
            gameForm->ShowDialog();  // Show TokenBattle form
            this->Close();  // Close StartForm after the TokenBattle form is opened
        }

        // Event to handle clearing the placeholder text if the textBox ix clicked
        void nameTextBox_GotFocus(System::Object^ sender, System::EventArgs^ e)
        {
            if (nameTextBox->Text == "Enter your name")
            {
                nameTextBox->Text = "";  // Clear the placeholder text
                nameTextBox->ForeColor = System::Drawing::Color::Black;  
            }
        }

        // Event to handle restoring placeholder text if empty
        void nameTextBox_LostFocus(System::Object^ sender, System::EventArgs^ e)
        {
            if (nameTextBox->Text == "")
            {
                nameTextBox->Text = "Enter your name";  // Restore the placeholder text
                nameTextBox->ForeColor = System::Drawing::Color::Gray; 
            }
        }

    private: System::Void StartForm_Load(System::Object^ sender, System::EventArgs^ e) {
        nameTextBox->Focus();
    }
 
#pragma endregion
    };
}

