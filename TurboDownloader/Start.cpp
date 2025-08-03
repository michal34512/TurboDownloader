#define CURL_STATICLIB
#include <curl/curl.h>
#include <msclr/marshal_cppstd.h>
#include "Start.h"

#include "FilePathOperations.h"
#include "FileFetcher.h"
#include "Download.h"
#include "DownloadFactory.h"
#include "LogReporter.h"
#include "Merger.h"
#include "FFMpeg.h"
#include "StringOperations.h"

using namespace System;

using namespace System::Windows::Forms;
using namespace AdditionalTools;

[STAThreadAttribute]

#if defined(_DEBUG)
int main(int argc, wchar_t* argv[]) {
	wchar_t* path = argv[0];
	FilePathOperations::GetExecutableDirectory(path);
	Download::DownloadFactory::arguments.OutputFilePath = FilePathOperations::exeDir + L"\\Output.mp4";
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	WCHAR filepath[MAX_PATH];
	GetModuleFileNameW(NULL, filepath, MAX_PATH);
	const wchar_t* path = filepath;
	FilePathOperations::GetExecutableDirectory(path);
	Download::DownloadFactory::arguments.OutputFilePath = FilePathOperations::exeDir + L"\\Output.mp4";
#endif

	Application::EnableVisualStyles();

	Application::SetCompatibleTextRenderingDefault(false);

	TurboDownloader::Start form;

	// Create a Timer control
	Timer^ timer = gcnew Timer();
	timer->Interval = 100;
	timer->Tick += gcnew EventHandler(%form, &TurboDownloader::Start::TimerTick);
	timer->Enabled = true; // Start the timer

	FileFetcher::TemporaryFileCleanup(Download::DownloadFactory::arguments);
	
	Application::Run(%form);

}
namespace TurboDownloader {
	System::Void Start::TimerTick(System::Object^ sender, System::EventArgs^ e) {
		while (LogReporter::getMessageCount() > 0)
		{
			std::string message = LogReporter::popNextMessage();
			#if defined(_DEBUG)
			std::cout << message << std::endl;
			#endif
			System::String^ itemString = gcnew System::String(message.c_str());
			this->logTextbox->AppendText(itemString + Environment::NewLine);
		}
		Download::DownloadFactory::Update();
		this->DownloadProgress->Value = Download::DownloadFactory::GetProgressPercentage();
		this->Percentage->Text = this->DownloadProgress->Value.ToString()+"%";
			
	}
	System::Void Start::Start_Load(System::Object^ sender, System::EventArgs^ e) {
		//header combobox
		auto headerFiles = FilePathOperations::GetFilesStartingWithPrefixFullPath(FilePathOperations::exeDir, L"header");
		for (std::wstring i : headerFiles)
		{
			System::String^ itemString = gcnew System::String(FilePathOperations::GetFilenameFromPath(i).c_str());
			this->headersCombo->Items->Add(itemString);
		}
		if(this->headersCombo->Items->Count>0)
			this->headersCombo->SelectedIndex = 0;
		//cookies combobox
		auto cookieFiles = FilePathOperations::GetFilesStartingWithPrefixFullPath(FilePathOperations::exeDir, L"cookie");
		for (std::wstring i : cookieFiles)
		{
			System::String^ itemString = gcnew System::String(FilePathOperations::GetFilenameFromPath(i).c_str());
			this->cookieCombo->Items->Add(itemString);
		}
		if (this->cookieCombo->Items->Count > 0)
			this->cookieCombo->SelectedIndex = 0;
		//output filename
		this->OutputFilenameTextbox->Text = gcnew System::String(Download::DownloadFactory::arguments.OutputFilePath.c_str()); 
		//more settings
		this->SingleFileSize->Text = Download::DownloadFactory::arguments.SinglePartSize.ToString();
		this->DownloadRate->Text = Download::DownloadFactory::arguments.DownloadRate.ToString();
		this->Prefix->Text = gcnew System::String(Download::DownloadFactory::arguments.Prefix.c_str());
		this->LowSpeedLimit->Text = Download::DownloadFactory::arguments.LowSpeedLimit.ToString();
		this->LowSpeedTime->Text = Download::DownloadFactory::arguments.LowSpeedTime.ToString();
		this->Verbose->Checked = Download::DownloadFactory::arguments.Verbose;
		this->UserAgent->Text = gcnew System::String(Download::DownloadFactory::arguments.UserAgent.c_str());


	}
	System::Void Start::Start_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e)
	{
		Download::Merger::End();
	}
	//Headers
	System::Void Start::headersCombo_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
	{
		ComboBox^ comboBox = dynamic_cast<ComboBox^>(sender);

		if (comboBox != nullptr && comboBox->SelectedItem != nullptr)
		{
			// Get the selected item's text
			String^ selectedItemText = comboBox->SelectedItem->ToString();
			this->headerTextbox->Text = selectedItemText;
			std::wstring wselectedItemText = msclr::interop::marshal_as<std::wstring>(selectedItemText);
			Download::DownloadFactory::arguments.InputHeaderFilePath = FilePathOperations::GetAbsuluteFilePath(wselectedItemText);
		}
	}
	System::Void Start::headerTextbox_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		TextBox^ textBox = dynamic_cast<TextBox^>(sender);
		if (textBox != nullptr && String::IsNullOrEmpty(textBox->Text) == false)
		{
			String^ textBoxText = textBox->Text->ToString();
			for each (Object ^ item in this->headersCombo->Items)
			{
				String^ itemText = dynamic_cast<String^>(item);
				if (itemText != nullptr && itemText->Equals(textBoxText))
				{
					int index = this->headersCombo->Items->IndexOf(item);
					if (index >= 0)
					{
						this->headersCombo->SelectedIndex = index;
						break;
					}
				}
			}
			std::wstring wselectedItemText = msclr::interop::marshal_as<std::wstring>(textBoxText);
			Download::DownloadFactory::arguments.InputHeaderFilePath = FilePathOperations::GetAbsuluteFilePath(wselectedItemText);
		}
	}
	System::Void Start::headerButton(System::Object^ sender, System::EventArgs^ e)
	{
		if (fileDialog->ShowDialog() == Windows::Forms::DialogResult::OK)
		{
			String^ selectedFilePath = fileDialog->FileName;
			this->headersCombo->SelectedIndex = -1;
			this->headerTextbox->Text = selectedFilePath;
			std::wstring wselectedItemText = msclr::interop::marshal_as<std::wstring>(selectedFilePath);
			Download::DownloadFactory::arguments.InputHeaderFilePath = FilePathOperations::GetAbsuluteFilePath(wselectedItemText);
		}
	}

	//Cookies
	System::Void Start::cookieCombo_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
	{
		ComboBox^ comboBox = dynamic_cast<ComboBox^>(sender);

		if (comboBox != nullptr && comboBox->SelectedItem != nullptr)
		{
			// Get the selected item's text
			String^ selectedItemText = comboBox->SelectedItem->ToString();
			this->cookieTextbox->Text = selectedItemText;
			std::wstring wselectedItemText = msclr::interop::marshal_as<std::wstring>(selectedItemText);
			Download::DownloadFactory::arguments.CookieFilePath = FilePathOperations::GetAbsuluteFilePath(wselectedItemText);
		}
	}
	System::Void Start::cookieTextbox_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		TextBox^ textBox = dynamic_cast<TextBox^>(sender);
		if (textBox != nullptr && String::IsNullOrEmpty(textBox->Text) == false)
		{
			String^ textBoxText = textBox->Text->ToString();
			for each (Object ^ item in this->cookieCombo->Items)
			{
				String^ itemText = dynamic_cast<String^>(item);
				if (itemText != nullptr && itemText->Equals(textBoxText))
				{
					int index = this->cookieCombo->Items->IndexOf(item);
					if (index >= 0)
					{
						this->cookieCombo->SelectedIndex = index;
						break;
					}
				}
			}
			std::wstring wselectedItemText = msclr::interop::marshal_as<std::wstring>(textBoxText);
			Download::DownloadFactory::arguments.CookieFilePath = FilePathOperations::GetAbsuluteFilePath(wselectedItemText);
		}
	}
	System::Void Start::cookieButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (fileDialog->ShowDialog() == Windows::Forms::DialogResult::OK)
		{
			String^ selectedFilePath = fileDialog->FileName;
			this->cookieCombo->SelectedIndex = -1;
			this->cookieTextbox->Text = selectedFilePath;
			std::wstring wselectedItemText = msclr::interop::marshal_as<std::wstring>(selectedFilePath);
			Download::DownloadFactory::arguments.CookieFilePath = FilePathOperations::GetAbsuluteFilePath(wselectedItemText);
		}
	}
	System::Void Start::URLTextbox_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		TextBox^ textBox = dynamic_cast<TextBox^>(sender);
		if (textBox != nullptr && String::IsNullOrEmpty(textBox->Text) == false)
		{
			String^ textBoxText = textBox->Text->ToString();
			Download::DownloadFactory::arguments.URL = msclr::interop::marshal_as<std::string>(textBoxText);
			StringOperations::remove_whitespace_characters(Download::DownloadFactory::arguments.URL);
			textBox->Text = msclr::interop::marshal_as<String^>(Download::DownloadFactory::arguments.URL);
		}
	}
	System::Void Start::submitButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		
		Download::DownloadFactory::CreateDownload();
		Download::DownloadFactory::Start();
	}
	System::Void Start::SingleFileSize_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		TextBox^ textBox = dynamic_cast<TextBox^>(sender);
		if (textBox != nullptr && String::IsNullOrEmpty(textBox->Text) == false)
		{
			std::string textBoxText = msclr::interop::marshal_as<std::string>(textBox->Text->ToString());
			try {
				Download::DownloadFactory::arguments.SinglePartSize = std::stoi(textBoxText);
			}
			catch (...) {
				
			}
		}
	}
	System::Void Start::DownloadRate_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		TextBox^ textBox = dynamic_cast<TextBox^>(sender);
		if (textBox != nullptr && String::IsNullOrEmpty(textBox->Text) == false)
		{
			std::string textBoxText = msclr::interop::marshal_as<std::string>(textBox->Text->ToString());
			try {
				Download::DownloadFactory::arguments.DownloadRate = std::stoi(textBoxText);
			}
			catch (...) {

			}
		}
	}
	System::Void Start::Prefix_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		TextBox^ textBox = dynamic_cast<TextBox^>(sender);
		if (textBox != nullptr && String::IsNullOrEmpty(textBox->Text) == false)
		{
			std::wstring textBoxText = msclr::interop::marshal_as<std::wstring>(textBox->Text->ToString());
			Download::DownloadFactory::arguments.Prefix = textBoxText;
		}
	}
	System::Void Start::LowSpeedLimit_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		TextBox^ textBox = dynamic_cast<TextBox^>(sender);
		if (textBox != nullptr && String::IsNullOrEmpty(textBox->Text) == false)
		{
			std::string textBoxText = msclr::interop::marshal_as<std::string>(textBox->Text->ToString());
			try {
				Download::DownloadFactory::arguments.LowSpeedLimit = std::stoi(textBoxText);
			}
			catch (...) {

			}
		}
	}
	System::Void Start::LowSpeedTime_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		TextBox^ textBox = dynamic_cast<TextBox^>(sender);
		if (textBox != nullptr && String::IsNullOrEmpty(textBox->Text) == false)
		{
			std::string textBoxText = msclr::interop::marshal_as<std::string>(textBox->Text->ToString());
			try {
				Download::DownloadFactory::arguments.LowSpeedTime = std::stoi(textBoxText);
			}
			catch (...) {

			}
		}
	}
	System::Void Start::Verbose_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		CheckBox^ checkBox = dynamic_cast<CheckBox^>(sender);
		if (checkBox != nullptr)
		{
			Download::DownloadFactory::arguments.Verbose = checkBox->Checked;
		}
	}
	System::Void Start::UserAgent_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		TextBox^ textBox = dynamic_cast<TextBox^>(sender);
		if (textBox != nullptr && String::IsNullOrEmpty(textBox->Text) == false)
		{
			std::string textBoxText = msclr::interop::marshal_as<std::string>(textBox->Text->ToString());
			Download::DownloadFactory::arguments.UserAgent = textBoxText;
		}
	}
	System::Void Start::OutputFilenameTextbox_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		TextBox^ textBox = dynamic_cast<TextBox^>(sender);
		if (textBox != nullptr && String::IsNullOrEmpty(textBox->Text) == false)
		{
			std::wstring textBoxText = msclr::interop::marshal_as<std::wstring>(textBox->Text->ToString());
			Download::DownloadFactory::arguments.OutputFilePath = textBoxText;
		}
	}
}