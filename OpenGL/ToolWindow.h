#pragma once

namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ToolWindow
	/// </summary>
	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public:
		static bool RenderInvertColorsChannel;
		static float YChannel;
		static float UChannel;
		static float VChannel;

		ToolWindow(void)
		{
			InitializeComponent();
			RenderInvertColorsChannel = InvertColorsCheckBox->Checked;
			YChannel = 100.0f;
			UChannel = 100.0f;
			VChannel = 100.0f;

			// Range of Trackbars
			trackBarY->Minimum = 0;
			trackBarY->Maximum = 200;
			trackBarY->Value = 100;

			trackBarU->Minimum = 0;
			trackBarU->Maximum = 200;
			trackBarU->Value = 100;

			trackBarV->Minimum = 0;
			trackBarV->Maximum = 200;
			trackBarV->Value = 100;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TrackBar^ trackBarY;
	private: System::Windows::Forms::TrackBar^ trackBarU;
	private: System::Windows::Forms::TrackBar^ trackBarV;
	protected:

	protected:


	private: System::Windows::Forms::CheckBox^ InvertColorsCheckBox;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ Vlabel;

	private: System::Windows::Forms::Label^ Ulabel;

	private: System::Windows::Forms::Label^ Ylabel;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>



		void InitializeComponent(void)
		{
			this->trackBarY = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarU = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarV = (gcnew System::Windows::Forms::TrackBar());
			this->InvertColorsCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->Vlabel = (gcnew System::Windows::Forms::Label());
			this->Ulabel = (gcnew System::Windows::Forms::Label());
			this->Ylabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarU))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarV))->BeginInit();
			this->SuspendLayout();
			// 
			// trackBarY
			// 
			this->trackBarY->BackColor = System::Drawing::SystemColors::Control;
			this->trackBarY->Location = System::Drawing::Point(42, 32);
			this->trackBarY->Maximum = 200;
			this->trackBarY->Name = L"trackBarY";
			this->trackBarY->Size = System::Drawing::Size(441, 69);
			this->trackBarY->TabIndex = 0;
			this->trackBarY->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarY_Scroll);
			// 
			// trackBarU
			// 
			this->trackBarU->Location = System::Drawing::Point(42, 107);
			this->trackBarU->Maximum = 200;
			this->trackBarU->Name = L"trackBarU";
			this->trackBarU->Size = System::Drawing::Size(441, 69);
			this->trackBarU->TabIndex = 1;
			this->trackBarU->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarU_Scroll);
			// 
			// trackBarV
			// 
			this->trackBarV->Location = System::Drawing::Point(42, 182);
			this->trackBarV->Maximum = 200;
			this->trackBarV->Name = L"trackBarV";
			this->trackBarV->Size = System::Drawing::Size(441, 69);
			this->trackBarV->TabIndex = 2;
			this->trackBarV->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarV_Scroll);
			// 
			// InvertColorsCheckBox
			// 
			this->InvertColorsCheckBox->AutoSize = true;
			this->InvertColorsCheckBox->Location = System::Drawing::Point(54, 257);
			this->InvertColorsCheckBox->Name = L"InvertColorsCheckBox";
			this->InvertColorsCheckBox->Size = System::Drawing::Size(124, 24);
			this->InvertColorsCheckBox->TabIndex = 3;
			this->InvertColorsCheckBox->Text = L"Invert Colors";
			this->InvertColorsCheckBox->UseVisualStyleBackColor = true;
			this->InvertColorsCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::InvertColorsCheckBox_CheckedChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 32);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(20, 20);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Y";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 107);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(21, 20);
			this->label2->TabIndex = 5;
			this->label2->Text = L"U";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(17, 182);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(20, 20);
			this->label3->TabIndex = 6;
			this->label3->Text = L"V";
			// 
			// Vlabel
			// 
			this->Vlabel->AutoSize = true;
			this->Vlabel->Location = System::Drawing::Point(490, 195);
			this->Vlabel->Name = L"Vlabel";
			this->Vlabel->Size = System::Drawing::Size(50, 20);
			this->Vlabel->TabIndex = 7;
			this->Vlabel->Text = L"100%";
			// 
			// Ulabel
			// 
			this->Ulabel->AutoSize = true;
			this->Ulabel->Location = System::Drawing::Point(490, 118);
			this->Ulabel->Name = L"Ulabel";
			this->Ulabel->Size = System::Drawing::Size(50, 20);
			this->Ulabel->TabIndex = 8;
			this->Ulabel->Text = L"100%";
			// 
			// Ylabel
			// 
			this->Ylabel->AutoSize = true;
			this->Ylabel->Location = System::Drawing::Point(490, 43);
			this->Ylabel->Name = L"Ylabel";
			this->Ylabel->Size = System::Drawing::Size(50, 20);
			this->Ylabel->TabIndex = 9;
			this->Ylabel->Text = L"100%";
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(557, 288);
			this->Controls->Add(this->Ylabel);
			this->Controls->Add(this->Ulabel);
			this->Controls->Add(this->Vlabel);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->InvertColorsCheckBox);
			this->Controls->Add(this->trackBarV);
			this->Controls->Add(this->trackBarU);
			this->Controls->Add(this->trackBarY);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarU))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarV))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void InvertColorsCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		RenderInvertColorsChannel = InvertColorsCheckBox->Checked;
		//YChannel = 200 - YChannel;
	}
	private: System::Void trackBarY_Scroll(System::Object^ sender, System::EventArgs^ e) {
		String^ YLabel = "100%";

		YChannel = (float)trackBarY->Value;
		YLabel = trackBarY->Value.ToString() + "%";
		Ylabel->Text = YLabel;
	}
	private: System::Void trackBarU_Scroll(System::Object^ sender, System::EventArgs^ e) {
		String^ ULabel = "100%";

		UChannel = (float)trackBarU->Value;
		ULabel = trackBarU->Value.ToString() + "%";
		Ulabel->Text = ULabel;
	}
	private: System::Void trackBarV_Scroll(System::Object^ sender, System::EventArgs^ e) {
		String^ VLabel = "100%";

		VChannel = (float)trackBarV->Value;
		VLabel = trackBarV->Value.ToString() + "%";
		Vlabel->Text = VLabel;
	}
};
}
