#pragma once
#include "Download.h"

namespace TurboDownloader {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Podsumowanie informacji o Start
	/// </summary>
	public ref class Start : public System::Windows::Forms::Form
	{
	public:
		Start(void)
		{
			InitializeComponent();
			//
			//TODO: W tym miejscu dodaj kod konstruktora
			//
		}

	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~Start()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ URLTextbox;
	private: System::Windows::Forms::Button^ SubmitButton;
	private: System::Windows::Forms::ProgressBar^ DownloadProgress;
	protected:

	protected:



	private: System::Windows::Forms::Button^ button2;





	private: System::Windows::Forms::Panel^ panel1;

	private: System::Windows::Forms::Button^ cookieButton;
	private: System::Windows::Forms::TextBox^ cookieTextbox;



	private: System::Windows::Forms::TextBox^ headerTextbox;

	private: System::Windows::Forms::ComboBox^ headersCombo;
	private: System::Windows::Forms::ComboBox^ cookieCombo;


	private: System::Windows::Forms::OpenFileDialog^ fileDialog;
	private: System::Windows::Forms::TextBox^ OutputFilenameTextbox;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ logTextbox;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Label^ DownloadRateLabel;

	private: System::Windows::Forms::Label^ SingleFileSizeLabel;
	private: System::Windows::Forms::Label^ PrefixLabel;
	private: System::Windows::Forms::TextBox^ Prefix;



	private: System::Windows::Forms::TextBox^ DownloadRate;

	private: System::Windows::Forms::TextBox^ SingleFileSize;
	private: System::Windows::Forms::TextBox^ LowSpeedTime;


	private: System::Windows::Forms::TextBox^ LowSpeedLimit;

	private: System::Windows::Forms::Label^ LowSpeedTimeLabel;

	private: System::Windows::Forms::Label^ LowSpeedLimitLabel;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::CheckBox^ Verbose;
	private: System::Windows::Forms::Label^ UserAgentLabel;
	private: System::Windows::Forms::TextBox^ UserAgent;
	private: System::Windows::Forms::Label^ URL;
	private: System::Windows::Forms::Label^ Percentage;




	protected:

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Start::typeid));
			this->URLTextbox = (gcnew System::Windows::Forms::TextBox());
			this->SubmitButton = (gcnew System::Windows::Forms::Button());
			this->DownloadProgress = (gcnew System::Windows::Forms::ProgressBar());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->UserAgentLabel = (gcnew System::Windows::Forms::Label());
			this->UserAgent = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->Verbose = (gcnew System::Windows::Forms::CheckBox());
			this->LowSpeedTime = (gcnew System::Windows::Forms::TextBox());
			this->LowSpeedLimit = (gcnew System::Windows::Forms::TextBox());
			this->LowSpeedTimeLabel = (gcnew System::Windows::Forms::Label());
			this->LowSpeedLimitLabel = (gcnew System::Windows::Forms::Label());
			this->PrefixLabel = (gcnew System::Windows::Forms::Label());
			this->Prefix = (gcnew System::Windows::Forms::TextBox());
			this->DownloadRate = (gcnew System::Windows::Forms::TextBox());
			this->SingleFileSize = (gcnew System::Windows::Forms::TextBox());
			this->DownloadRateLabel = (gcnew System::Windows::Forms::Label());
			this->SingleFileSizeLabel = (gcnew System::Windows::Forms::Label());
			this->cookieButton = (gcnew System::Windows::Forms::Button());
			this->cookieTextbox = (gcnew System::Windows::Forms::TextBox());
			this->headerTextbox = (gcnew System::Windows::Forms::TextBox());
			this->headersCombo = (gcnew System::Windows::Forms::ComboBox());
			this->cookieCombo = (gcnew System::Windows::Forms::ComboBox());
			this->fileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->OutputFilenameTextbox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->logTextbox = (gcnew System::Windows::Forms::TextBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->URL = (gcnew System::Windows::Forms::Label());
			this->Percentage = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// URLTextbox
			// 
			this->URLTextbox->Location = System::Drawing::Point(12, 37);
			this->URLTextbox->Name = L"URLTextbox";
			this->URLTextbox->Size = System::Drawing::Size(550, 20);
			this->URLTextbox->TabIndex = 0;
			this->URLTextbox->TextChanged += gcnew System::EventHandler(this, &Start::URLTextbox_TextChanged);
			// 
			// SubmitButton
			// 
			this->SubmitButton->BackColor = System::Drawing::Color::Lime;
			this->SubmitButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->SubmitButton->Location = System::Drawing::Point(411, 62);
			this->SubmitButton->Name = L"SubmitButton";
			this->SubmitButton->Size = System::Drawing::Size(151, 47);
			this->SubmitButton->TabIndex = 1;
			this->SubmitButton->Text = L"Apply";
			this->SubmitButton->UseVisualStyleBackColor = false;
			this->SubmitButton->Click += gcnew System::EventHandler(this, &Start::submitButton_Click);
			// 
			// DownloadProgress
			// 
			this->DownloadProgress->Location = System::Drawing::Point(12, 451);
			this->DownloadProgress->Name = L"DownloadProgress";
			this->DownloadProgress->Size = System::Drawing::Size(464, 31);
			this->DownloadProgress->TabIndex = 2;
			this->DownloadProgress->Value = 10;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 63);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(56, 20);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Headers";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Start::headerButton);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::Info;
			this->panel1->Controls->Add(this->UserAgentLabel);
			this->panel1->Controls->Add(this->UserAgent);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->Verbose);
			this->panel1->Controls->Add(this->LowSpeedTime);
			this->panel1->Controls->Add(this->LowSpeedLimit);
			this->panel1->Controls->Add(this->LowSpeedTimeLabel);
			this->panel1->Controls->Add(this->LowSpeedLimitLabel);
			this->panel1->Controls->Add(this->PrefixLabel);
			this->panel1->Controls->Add(this->Prefix);
			this->panel1->Controls->Add(this->DownloadRate);
			this->panel1->Controls->Add(this->SingleFileSize);
			this->panel1->Controls->Add(this->DownloadRateLabel);
			this->panel1->Controls->Add(this->SingleFileSizeLabel);
			this->panel1->Location = System::Drawing::Point(12, 141);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(550, 112);
			this->panel1->TabIndex = 6;
			// 
			// UserAgentLabel
			// 
			this->UserAgentLabel->AutoSize = true;
			this->UserAgentLabel->Location = System::Drawing::Point(3, 92);
			this->UserAgentLabel->Name = L"UserAgentLabel";
			this->UserAgentLabel->Size = System::Drawing::Size(62, 13);
			this->UserAgentLabel->TabIndex = 17;
			this->UserAgentLabel->Text = L"User agent:";
			// 
			// UserAgent
			// 
			this->UserAgent->Location = System::Drawing::Point(65, 89);
			this->UserAgent->Name = L"UserAgent";
			this->UserAgent->Size = System::Drawing::Size(482, 20);
			this->UserAgent->TabIndex = 16;
			this->UserAgent->TextChanged += gcnew System::EventHandler(this, &Start::UserAgent_TextChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->ForeColor = System::Drawing::Color::Silver;
			this->label4->Location = System::Drawing::Point(0, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(70, 13);
			this->label4->TabIndex = 15;
			this->label4->Text = L"More settings";
			// 
			// Verbose
			// 
			this->Verbose->AutoSize = true;
			this->Verbose->Location = System::Drawing::Point(329, 64);
			this->Verbose->Name = L"Verbose";
			this->Verbose->Size = System::Drawing::Size(65, 17);
			this->Verbose->TabIndex = 11;
			this->Verbose->Text = L"Verbose";
			this->Verbose->UseVisualStyleBackColor = true;
			this->Verbose->CheckedChanged += gcnew System::EventHandler(this, &Start::Verbose_CheckedChanged);
			// 
			// LowSpeedTime
			// 
			this->LowSpeedTime->Location = System::Drawing::Point(364, 34);
			this->LowSpeedTime->Name = L"LowSpeedTime";
			this->LowSpeedTime->Size = System::Drawing::Size(100, 20);
			this->LowSpeedTime->TabIndex = 9;
			this->LowSpeedTime->TextChanged += gcnew System::EventHandler(this, &Start::LowSpeedTime_TextChanged);
			// 
			// LowSpeedLimit
			// 
			this->LowSpeedLimit->Location = System::Drawing::Point(364, 8);
			this->LowSpeedLimit->Name = L"LowSpeedLimit";
			this->LowSpeedLimit->Size = System::Drawing::Size(100, 20);
			this->LowSpeedLimit->TabIndex = 8;
			this->LowSpeedLimit->TextChanged += gcnew System::EventHandler(this, &Start::LowSpeedLimit_TextChanged);
			// 
			// LowSpeedTimeLabel
			// 
			this->LowSpeedTimeLabel->AutoSize = true;
			this->LowSpeedTimeLabel->Location = System::Drawing::Point(279, 37);
			this->LowSpeedTimeLabel->Name = L"LowSpeedTimeLabel";
			this->LowSpeedTimeLabel->Size = System::Drawing::Size(84, 13);
			this->LowSpeedTimeLabel->TabIndex = 7;
			this->LowSpeedTimeLabel->Text = L"Low speed time:";
			// 
			// LowSpeedLimitLabel
			// 
			this->LowSpeedLimitLabel->AutoSize = true;
			this->LowSpeedLimitLabel->Location = System::Drawing::Point(281, 11);
			this->LowSpeedLimitLabel->Name = L"LowSpeedLimitLabel";
			this->LowSpeedLimitLabel->Size = System::Drawing::Size(82, 13);
			this->LowSpeedLimitLabel->TabIndex = 6;
			this->LowSpeedLimitLabel->Text = L"Low speed limit:";
			// 
			// PrefixLabel
			// 
			this->PrefixLabel->AutoSize = true;
			this->PrefixLabel->Location = System::Drawing::Point(116, 64);
			this->PrefixLabel->Name = L"PrefixLabel";
			this->PrefixLabel->Size = System::Drawing::Size(36, 13);
			this->PrefixLabel->TabIndex = 5;
			this->PrefixLabel->Text = L"Prefix:";
			// 
			// Prefix
			// 
			this->Prefix->Location = System::Drawing::Point(153, 61);
			this->Prefix->Name = L"Prefix";
			this->Prefix->Size = System::Drawing::Size(100, 20);
			this->Prefix->TabIndex = 4;
			this->Prefix->TextChanged += gcnew System::EventHandler(this, &Start::Prefix_TextChanged);
			// 
			// DownloadRate
			// 
			this->DownloadRate->Location = System::Drawing::Point(153, 34);
			this->DownloadRate->Name = L"DownloadRate";
			this->DownloadRate->Size = System::Drawing::Size(100, 20);
			this->DownloadRate->TabIndex = 3;
			this->DownloadRate->TextChanged += gcnew System::EventHandler(this, &Start::DownloadRate_TextChanged);
			// 
			// SingleFileSize
			// 
			this->SingleFileSize->Location = System::Drawing::Point(153, 8);
			this->SingleFileSize->Name = L"SingleFileSize";
			this->SingleFileSize->Size = System::Drawing::Size(100, 20);
			this->SingleFileSize->TabIndex = 2;
			this->SingleFileSize->TextChanged += gcnew System::EventHandler(this, &Start::SingleFileSize_TextChanged);
			// 
			// DownloadRateLabel
			// 
			this->DownloadRateLabel->AutoSize = true;
			this->DownloadRateLabel->Location = System::Drawing::Point(73, 37);
			this->DownloadRateLabel->Name = L"DownloadRateLabel";
			this->DownloadRateLabel->Size = System::Drawing::Size(79, 13);
			this->DownloadRateLabel->TabIndex = 1;
			this->DownloadRateLabel->Text = L"Download rate:";
			// 
			// SingleFileSizeLabel
			// 
			this->SingleFileSizeLabel->AutoSize = true;
			this->SingleFileSizeLabel->Location = System::Drawing::Point(76, 11);
			this->SingleFileSizeLabel->Name = L"SingleFileSizeLabel";
			this->SingleFileSizeLabel->Size = System::Drawing::Size(76, 13);
			this->SingleFileSizeLabel->TabIndex = 0;
			this->SingleFileSizeLabel->Text = L"Single file size:";
			// 
			// cookieButton
			// 
			this->cookieButton->Location = System::Drawing::Point(12, 89);
			this->cookieButton->Name = L"cookieButton";
			this->cookieButton->Size = System::Drawing::Size(56, 20);
			this->cookieButton->TabIndex = 7;
			this->cookieButton->Text = L"Cookies";
			this->cookieButton->UseVisualStyleBackColor = true;
			this->cookieButton->Click += gcnew System::EventHandler(this, &Start::cookieButton_Click);
			// 
			// cookieTextbox
			// 
			this->cookieTextbox->Location = System::Drawing::Point(198, 88);
			this->cookieTextbox->Name = L"cookieTextbox";
			this->cookieTextbox->Size = System::Drawing::Size(207, 20);
			this->cookieTextbox->TabIndex = 8;
			this->cookieTextbox->TextChanged += gcnew System::EventHandler(this, &Start::cookieTextbox_TextChanged);
			// 
			// headerTextbox
			// 
			this->headerTextbox->Location = System::Drawing::Point(198, 62);
			this->headerTextbox->Name = L"headerTextbox";
			this->headerTextbox->Size = System::Drawing::Size(207, 20);
			this->headerTextbox->TabIndex = 9;
			this->headerTextbox->TextChanged += gcnew System::EventHandler(this, &Start::headerTextbox_TextChanged);
			// 
			// headersCombo
			// 
			this->headersCombo->FormattingEnabled = true;
			this->headersCombo->Location = System::Drawing::Point(74, 62);
			this->headersCombo->Name = L"headersCombo";
			this->headersCombo->Size = System::Drawing::Size(118, 21);
			this->headersCombo->TabIndex = 10;
			this->headersCombo->SelectedIndexChanged += gcnew System::EventHandler(this, &Start::headersCombo_SelectedIndexChanged);
			// 
			// cookieCombo
			// 
			this->cookieCombo->FormattingEnabled = true;
			this->cookieCombo->Location = System::Drawing::Point(74, 88);
			this->cookieCombo->Name = L"cookieCombo";
			this->cookieCombo->Size = System::Drawing::Size(118, 21);
			this->cookieCombo->TabIndex = 11;
			this->cookieCombo->SelectedIndexChanged += gcnew System::EventHandler(this, &Start::cookieCombo_SelectedIndexChanged);
			// 
			// fileDialog
			// 
			this->fileDialog->FileName = L"file";
			this->fileDialog->Filter = L"Text Files|*.txt|All Files|*.*";
			// 
			// OutputFilenameTextbox
			// 
			this->OutputFilenameTextbox->Location = System::Drawing::Point(130, 118);
			this->OutputFilenameTextbox->Name = L"OutputFilenameTextbox";
			this->OutputFilenameTextbox->Size = System::Drawing::Size(432, 20);
			this->OutputFilenameTextbox->TabIndex = 12;
			this->OutputFilenameTextbox->TextChanged += gcnew System::EventHandler(this, &Start::OutputFilenameTextbox_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label1->Location = System::Drawing::Point(15, 121);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(112, 17);
			this->label1->TabIndex = 13;
			this->label1->Text = L"Output filename:";
			// 
			// logTextbox
			// 
			this->logTextbox->BackColor = System::Drawing::SystemColors::ControlLight;
			this->logTextbox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->logTextbox->Location = System::Drawing::Point(0, 0);
			this->logTextbox->Multiline = true;
			this->logTextbox->Name = L"logTextbox";
			this->logTextbox->ReadOnly = true;
			this->logTextbox->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->logTextbox->Size = System::Drawing::Size(550, 186);
			this->logTextbox->TabIndex = 14;
			this->logTextbox->WordWrap = false;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->logTextbox);
			this->panel2->Location = System::Drawing::Point(12, 259);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(550, 186);
			this->panel2->TabIndex = 15;
			// 
			// URL
			// 
			this->URL->AutoSize = true;
			this->URL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->URL->Location = System::Drawing::Point(253, 3);
			this->URL->Name = L"URL";
			this->URL->Size = System::Drawing::Size(72, 31);
			this->URL->TabIndex = 16;
			this->URL->Text = L"URL";
			// 
			// Percentage
			// 
			this->Percentage->AutoSize = true;
			this->Percentage->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->Percentage->Location = System::Drawing::Point(482, 451);
			this->Percentage->Name = L"Percentage";
			this->Percentage->Size = System::Drawing::Size(83, 31);
			this->Percentage->TabIndex = 17;
			this->Percentage->Text = L"100%";
			// 
			// Start
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(584, 491);
			this->Controls->Add(this->Percentage);
			this->Controls->Add(this->URL);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->OutputFilenameTextbox);
			this->Controls->Add(this->cookieCombo);
			this->Controls->Add(this->headersCombo);
			this->Controls->Add(this->headerTextbox);
			this->Controls->Add(this->cookieTextbox);
			this->Controls->Add(this->cookieButton);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->DownloadProgress);
			this->Controls->Add(this->SubmitButton);
			this->Controls->Add(this->URLTextbox);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(600, 530);
			this->MinimumSize = System::Drawing::Size(600, 530);
			this->Name = L"Start";
			this->Text = L"Turbo Downloader";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Start::Start_FormClosed);
			this->Load += gcnew System::EventHandler(this, &Start::Start_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	#pragma endregion
	public: System::Void TimerTick(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Start_Load(System::Object^ sender, System::EventArgs^ e); 
	private: System::Void headersCombo_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void headerTextbox_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void headerButton(System::Object^ sender, System::EventArgs^ e);
	private: System::Void cookieCombo_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void cookieTextbox_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void cookieButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void submitButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void URLTextbox_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Start_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);
	private: System::Void SingleFileSize_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void DownloadRate_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Prefix_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void LowSpeedLimit_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void LowSpeedTime_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Verbose_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void UserAgent_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void OutputFilenameTextbox_TextChanged(System::Object^ sender, System::EventArgs^ e);
};
}
