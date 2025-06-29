#include "StartForm.h"
#include "TokenBattle.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    //Show the StartForm form first
    AlgorithmsProjectGroup16::StartForm^ startForm = gcnew AlgorithmsProjectGroup16::StartForm();


    if (startForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        // If the user clicks "Start Game", run the TokenBattle form.
        Application::Run(gcnew AlgorithmsProjectGroup16::TokenBattle());  
    }
}
