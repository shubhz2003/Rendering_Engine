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
		static float trackBar_R;
		static float trackBar_G;
		static float trackBar_B;
		static float trackBar_SpecStrength;
		static float trackBar_Frequency;
		static float trackBar_Amplitude;
		static bool resetLight_Btn;
		static bool resetTransform_Btn;
		static bool moveLight_Channel;
		static bool transform_Channel;
		static bool waterScene_Channel;
		static bool spaceScene_Channel;
		static bool RenderTranslate_Channel;
		static bool RenderRotate_Channel;
		static bool RenderScale_Channel;
		static bool RenderWireframe_Channel;
		static bool RenderTintBlue_Channel;

		ToolWindow(void)
		{
			InitializeComponent();
			trackBar_R = 100.0f;
			trackBar_G = 100.0f;
			trackBar_B = 100.0f;
			trackBar_SpecStrength = 4.0f;
			trackBar_Frequency = 400.0f;
			trackBar_Amplitude = 1.0f;
			resetLight_Btn = false;
			resetTransform_Btn = false;
			moveLight_Channel = moveLightBtn->Checked;
			transform_Channel = transformBtn->Checked;
			waterScene_Channel = waterSceneBtn->Checked;
			spaceScene_Channel = spaceSceneBtn->Checked;
			RenderTranslate_Channel = checkBoxTranslate->Checked;
			RenderRotate_Channel = checkBoxRotate->Checked;
			RenderScale_Channel = checkBoxScale->Checked;
			RenderWireframe_Channel = checkBoxWireframeRender->Checked;
			RenderTintBlue_Channel = checkBoxTintBlue->Checked;
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
	private: System::Windows::Forms::RadioButton^ moveLightBtn;
	private: System::Windows::Forms::RadioButton^ transformBtn;
	private: System::Windows::Forms::RadioButton^ waterSceneBtn;
	private: System::Windows::Forms::RadioButton^ spaceSceneBtn;
	private: System::Windows::Forms::Button^ restLightPosBtn;
	private: System::Windows::Forms::Button^ resetTransformBtn;
	private: System::Windows::Forms::CheckBox^ checkBoxTranslate;

	private: System::Windows::Forms::CheckBox^ checkBoxRotate;

	private: System::Windows::Forms::CheckBox^ checkBoxScale;

	private: System::Windows::Forms::CheckBox^ checkBoxWireframeRender;
	private: System::Windows::Forms::CheckBox^ checkBoxTintBlue;


	protected:

	protected:


	private: System::Windows::Forms::TrackBar^ trackBar_SpecStrength_Component;
	private: System::Windows::Forms::TrackBar^ trackBar_R_Component;
	private: System::Windows::Forms::TrackBar^ trackBar_G_Component;
	private: System::Windows::Forms::TrackBar^ trackBar_B_Component;
	private: System::Windows::Forms::TrackBar^ trackBar_Frequency_Component;
	private: System::Windows::Forms::TrackBar^ trackBar_Amplitude_Component;
	private: System::Windows::Forms::Label^ amplitude_LblVal;


	private: System::Windows::Forms::Label^ SpecStrength_Lbl;
	private: System::Windows::Forms::Label^ SpecColor_Lbl;
	private: System::Windows::Forms::Label^ R_Label;

	private: System::Windows::Forms::Label^ G_Label;
	private: System::Windows::Forms::Label^ B_Label;
	private: System::Windows::Forms::Label^ frequency_Lbl;


	private: System::Windows::Forms::Label^ SpecStrength_LblVal;
	private: System::Windows::Forms::Label^ r_LblVal;
	private: System::Windows::Forms::Label^ amplitude_lbl;

	private: System::Windows::Forms::Label^ g_LblVal;
	private: System::Windows::Forms::Label^ b_LblVal;
	private: System::Windows::Forms::Label^ frequency_LblVal;


	protected:



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>



		void InitializeComponent(void)
		{
			this->moveLightBtn = (gcnew System::Windows::Forms::RadioButton());
			this->transformBtn = (gcnew System::Windows::Forms::RadioButton());
			this->waterSceneBtn = (gcnew System::Windows::Forms::RadioButton());
			this->spaceSceneBtn = (gcnew System::Windows::Forms::RadioButton());
			this->restLightPosBtn = (gcnew System::Windows::Forms::Button());
			this->resetTransformBtn = (gcnew System::Windows::Forms::Button());
			this->checkBoxTranslate = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxRotate = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxScale = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxWireframeRender = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxTintBlue = (gcnew System::Windows::Forms::CheckBox());
			this->trackBar_SpecStrength_Component = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar_R_Component = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar_G_Component = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar_B_Component = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar_Frequency_Component = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar_Amplitude_Component = (gcnew System::Windows::Forms::TrackBar());
			this->amplitude_LblVal = (gcnew System::Windows::Forms::Label());
			this->SpecStrength_Lbl = (gcnew System::Windows::Forms::Label());
			this->SpecColor_Lbl = (gcnew System::Windows::Forms::Label());
			this->R_Label = (gcnew System::Windows::Forms::Label());
			this->G_Label = (gcnew System::Windows::Forms::Label());
			this->B_Label = (gcnew System::Windows::Forms::Label());
			this->frequency_Lbl = (gcnew System::Windows::Forms::Label());
			this->SpecStrength_LblVal = (gcnew System::Windows::Forms::Label());
			this->r_LblVal = (gcnew System::Windows::Forms::Label());
			this->amplitude_lbl = (gcnew System::Windows::Forms::Label());
			this->g_LblVal = (gcnew System::Windows::Forms::Label());
			this->b_LblVal = (gcnew System::Windows::Forms::Label());
			this->frequency_LblVal = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_SpecStrength_Component))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_R_Component))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_G_Component))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_B_Component))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Frequency_Component))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Amplitude_Component))->BeginInit();
			this->SuspendLayout();
			// 
			// moveLightBtn
			// 
			this->moveLightBtn->AutoSize = true;
			this->moveLightBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->moveLightBtn->Location = System::Drawing::Point(41, 12);
			this->moveLightBtn->Name = L"moveLightBtn";
			this->moveLightBtn->Size = System::Drawing::Size(88, 17);
			this->moveLightBtn->TabIndex = 0;
			this->moveLightBtn->TabStop = true;
			this->moveLightBtn->Text = L"Move Light\r\n";
			this->moveLightBtn->UseVisualStyleBackColor = true;
			this->moveLightBtn->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::moveLightBtn_CheckedChanged);
			// 
			// transformBtn
			// 
			this->transformBtn->AutoSize = true;
			this->transformBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->transformBtn->Location = System::Drawing::Point(41, 235);
			this->transformBtn->Name = L"transformBtn";
			this->transformBtn->Size = System::Drawing::Size(81, 17);
			this->transformBtn->TabIndex = 1;
			this->transformBtn->TabStop = true;
			this->transformBtn->Text = L"Transform";
			this->transformBtn->UseVisualStyleBackColor = true;
			this->transformBtn->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::transformBtn_CheckedChanged);
			// 
			// waterSceneBtn
			// 
			this->waterSceneBtn->AutoSize = true;
			this->waterSceneBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->waterSceneBtn->Location = System::Drawing::Point(41, 376);
			this->waterSceneBtn->Name = L"waterSceneBtn";
			this->waterSceneBtn->Size = System::Drawing::Size(99, 17);
			this->waterSceneBtn->TabIndex = 2;
			this->waterSceneBtn->TabStop = true;
			this->waterSceneBtn->Text = L"Water Scene";
			this->waterSceneBtn->UseVisualStyleBackColor = true;
			this->waterSceneBtn->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::waterSceneBtn_CheckedChanged);
			// 
			// spaceSceneBtn
			// 
			this->spaceSceneBtn->AutoSize = true;
			this->spaceSceneBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->spaceSceneBtn->Location = System::Drawing::Point(41, 539);
			this->spaceSceneBtn->Name = L"spaceSceneBtn";
			this->spaceSceneBtn->Size = System::Drawing::Size(101, 17);
			this->spaceSceneBtn->TabIndex = 3;
			this->spaceSceneBtn->TabStop = true;
			this->spaceSceneBtn->Text = L"Space Scene";
			this->spaceSceneBtn->UseVisualStyleBackColor = true;
			this->spaceSceneBtn->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::spaceSceneBtn_CheckedChanged);
			// 
			// restLightPosBtn
			// 
			this->restLightPosBtn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->restLightPosBtn->Location = System::Drawing::Point(59, 35);
			this->restLightPosBtn->Name = L"restLightPosBtn";
			this->restLightPosBtn->Size = System::Drawing::Size(116, 23);
			this->restLightPosBtn->TabIndex = 4;
			this->restLightPosBtn->Text = L"Reset Light Position";
			this->restLightPosBtn->UseVisualStyleBackColor = true;
			this->restLightPosBtn->Click += gcnew System::EventHandler(this, &ToolWindow::restLightPosBtn_Click);
			// 
			// resetTransformBtn
			// 
			this->resetTransformBtn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->resetTransformBtn->Location = System::Drawing::Point(59, 259);
			this->resetTransformBtn->Name = L"resetTransformBtn";
			this->resetTransformBtn->Size = System::Drawing::Size(116, 23);
			this->resetTransformBtn->TabIndex = 5;
			this->resetTransformBtn->Text = L"Reset Transform";
			this->resetTransformBtn->UseVisualStyleBackColor = true;
			this->resetTransformBtn->Click += gcnew System::EventHandler(this, &ToolWindow::resetTransformBtn_Click);
			// 
			// checkBoxTranslate
			// 
			this->checkBoxTranslate->AutoSize = true;
			this->checkBoxTranslate->Location = System::Drawing::Point(74, 289);
			this->checkBoxTranslate->Name = L"checkBoxTranslate";
			this->checkBoxTranslate->Size = System::Drawing::Size(73, 17);
			this->checkBoxTranslate->TabIndex = 6;
			this->checkBoxTranslate->Text = L"Transform";
			this->checkBoxTranslate->UseVisualStyleBackColor = true;
			this->checkBoxTranslate->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxTranslate_CheckedChanged);
			// 
			// checkBoxRotate
			// 
			this->checkBoxRotate->AutoSize = true;
			this->checkBoxRotate->Location = System::Drawing::Point(74, 313);
			this->checkBoxRotate->Name = L"checkBoxRotate";
			this->checkBoxRotate->Size = System::Drawing::Size(58, 17);
			this->checkBoxRotate->TabIndex = 7;
			this->checkBoxRotate->Text = L"Rotate";
			this->checkBoxRotate->UseVisualStyleBackColor = true;
			this->checkBoxRotate->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxRotate_CheckedChanged);
			// 
			// checkBoxScale
			// 
			this->checkBoxScale->AutoSize = true;
			this->checkBoxScale->Location = System::Drawing::Point(74, 337);
			this->checkBoxScale->Name = L"checkBoxScale";
			this->checkBoxScale->Size = System::Drawing::Size(53, 17);
			this->checkBoxScale->TabIndex = 8;
			this->checkBoxScale->Text = L"Scale";
			this->checkBoxScale->UseVisualStyleBackColor = true;
			this->checkBoxScale->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxScale_CheckedChanged);
			// 
			// checkBoxWireframeRender
			// 
			this->checkBoxWireframeRender->AutoSize = true;
			this->checkBoxWireframeRender->Location = System::Drawing::Point(74, 486);
			this->checkBoxWireframeRender->Name = L"checkBoxWireframeRender";
			this->checkBoxWireframeRender->Size = System::Drawing::Size(112, 17);
			this->checkBoxWireframeRender->TabIndex = 9;
			this->checkBoxWireframeRender->Text = L"Wireframe Render";
			this->checkBoxWireframeRender->UseVisualStyleBackColor = true;
			this->checkBoxWireframeRender->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxWireframeRender_CheckedChanged);
			// 
			// checkBoxTintBlue
			// 
			this->checkBoxTintBlue->AutoSize = true;
			this->checkBoxTintBlue->Location = System::Drawing::Point(74, 516);
			this->checkBoxTintBlue->Name = L"checkBoxTintBlue";
			this->checkBoxTintBlue->Size = System::Drawing::Size(68, 17);
			this->checkBoxTintBlue->TabIndex = 10;
			this->checkBoxTintBlue->Text = L"Tint Blue";
			this->checkBoxTintBlue->UseVisualStyleBackColor = true;
			this->checkBoxTintBlue->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxTintBlue_CheckedChanged);
			// 
			// trackBar_SpecStrength_Component
			// 
			this->trackBar_SpecStrength_Component->Location = System::Drawing::Point(128, 73);
			this->trackBar_SpecStrength_Component->Maximum = 128;
			this->trackBar_SpecStrength_Component->Minimum = 1;
			this->trackBar_SpecStrength_Component->Name = L"trackBar_SpecStrength_Component";
			this->trackBar_SpecStrength_Component->Size = System::Drawing::Size(265, 45);
			this->trackBar_SpecStrength_Component->TabIndex = 11;
			this->trackBar_SpecStrength_Component->Value = 4;
			this->trackBar_SpecStrength_Component->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_SpecStrength_Component_Scroll);
			// 
			// trackBar_R_Component
			// 
			this->trackBar_R_Component->Location = System::Drawing::Point(128, 105);
			this->trackBar_R_Component->Maximum = 300;
			this->trackBar_R_Component->Name = L"trackBar_R_Component";
			this->trackBar_R_Component->Size = System::Drawing::Size(265, 45);
			this->trackBar_R_Component->TabIndex = 12;
			this->trackBar_R_Component->Value = 100;
			this->trackBar_R_Component->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_R_Component_Scroll);
			// 
			// trackBar_G_Component
			// 
			this->trackBar_G_Component->Location = System::Drawing::Point(128, 145);
			this->trackBar_G_Component->Maximum = 300;
			this->trackBar_G_Component->Name = L"trackBar_G_Component";
			this->trackBar_G_Component->Size = System::Drawing::Size(265, 45);
			this->trackBar_G_Component->TabIndex = 13;
			this->trackBar_G_Component->Value = 100;
			this->trackBar_G_Component->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_G_Component_Scroll);
			// 
			// trackBar_B_Component
			// 
			this->trackBar_B_Component->Location = System::Drawing::Point(128, 184);
			this->trackBar_B_Component->Maximum = 300;
			this->trackBar_B_Component->Name = L"trackBar_B_Component";
			this->trackBar_B_Component->Size = System::Drawing::Size(265, 45);
			this->trackBar_B_Component->TabIndex = 14;
			this->trackBar_B_Component->Value = 100;
			this->trackBar_B_Component->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_B_Component_Scroll);
			// 
			// trackBar_Frequency_Component
			// 
			this->trackBar_Frequency_Component->Location = System::Drawing::Point(128, 393);
			this->trackBar_Frequency_Component->Maximum = 400;
			this->trackBar_Frequency_Component->Name = L"trackBar_Frequency_Component";
			this->trackBar_Frequency_Component->Size = System::Drawing::Size(265, 45);
			this->trackBar_Frequency_Component->TabIndex = 15;
			this->trackBar_Frequency_Component->Value = 400;
			this->trackBar_Frequency_Component->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_Frequency_Component_Scroll);
			// 
			// trackBar_Amplitude_Component
			// 
			this->trackBar_Amplitude_Component->Location = System::Drawing::Point(128, 435);
			this->trackBar_Amplitude_Component->Maximum = 100;
			this->trackBar_Amplitude_Component->Name = L"trackBar_Amplitude_Component";
			this->trackBar_Amplitude_Component->Size = System::Drawing::Size(265, 45);
			this->trackBar_Amplitude_Component->TabIndex = 16;
			this->trackBar_Amplitude_Component->Value = 1;
			this->trackBar_Amplitude_Component->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_Amplitude_Component_Scroll);
			// 
			// amplitude_LblVal
			// 
			this->amplitude_LblVal->AutoSize = true;
			this->amplitude_LblVal->Location = System::Drawing::Point(412, 435);
			this->amplitude_LblVal->Name = L"amplitude_LblVal";
			this->amplitude_LblVal->Size = System::Drawing::Size(28, 13);
			this->amplitude_LblVal->TabIndex = 17;
			this->amplitude_LblVal->Text = L"0.01";
			// 
			// SpecStrength_Lbl
			// 
			this->SpecStrength_Lbl->AutoSize = true;
			this->SpecStrength_Lbl->Location = System::Drawing::Point(12, 73);
			this->SpecStrength_Lbl->Name = L"SpecStrength_Lbl";
			this->SpecStrength_Lbl->Size = System::Drawing::Size(92, 13);
			this->SpecStrength_Lbl->TabIndex = 18;
			this->SpecStrength_Lbl->Text = L"Specular Strength";
			// 
			// SpecColor_Lbl
			// 
			this->SpecColor_Lbl->AutoSize = true;
			this->SpecColor_Lbl->Location = System::Drawing::Point(12, 104);
			this->SpecColor_Lbl->Name = L"SpecColor_Lbl";
			this->SpecColor_Lbl->Size = System::Drawing::Size(76, 13);
			this->SpecColor_Lbl->TabIndex = 19;
			this->SpecColor_Lbl->Text = L"Specular Color";
			// 
			// R_Label
			// 
			this->R_Label->AutoSize = true;
			this->R_Label->Location = System::Drawing::Point(96, 104);
			this->R_Label->Name = L"R_Label";
			this->R_Label->Size = System::Drawing::Size(15, 13);
			this->R_Label->TabIndex = 20;
			this->R_Label->Text = L"R";
			// 
			// G_Label
			// 
			this->G_Label->AutoSize = true;
			this->G_Label->Location = System::Drawing::Point(99, 145);
			this->G_Label->Name = L"G_Label";
			this->G_Label->Size = System::Drawing::Size(15, 13);
			this->G_Label->TabIndex = 21;
			this->G_Label->Text = L"G";
			// 
			// B_Label
			// 
			this->B_Label->AutoSize = true;
			this->B_Label->Location = System::Drawing::Point(99, 184);
			this->B_Label->Name = L"B_Label";
			this->B_Label->Size = System::Drawing::Size(14, 13);
			this->B_Label->TabIndex = 22;
			this->B_Label->Text = L"B";
			// 
			// frequency_Lbl
			// 
			this->frequency_Lbl->AutoSize = true;
			this->frequency_Lbl->Location = System::Drawing::Point(38, 396);
			this->frequency_Lbl->Name = L"frequency_Lbl";
			this->frequency_Lbl->Size = System::Drawing::Size(57, 13);
			this->frequency_Lbl->TabIndex = 23;
			this->frequency_Lbl->Text = L"Frequency";
			// 
			// SpecStrength_LblVal
			// 
			this->SpecStrength_LblVal->AutoSize = true;
			this->SpecStrength_LblVal->Location = System::Drawing::Point(400, 73);
			this->SpecStrength_LblVal->Name = L"SpecStrength_LblVal";
			this->SpecStrength_LblVal->Size = System::Drawing::Size(13, 13);
			this->SpecStrength_LblVal->TabIndex = 24;
			this->SpecStrength_LblVal->Text = L"4";
			// 
			// r_LblVal
			// 
			this->r_LblVal->AutoSize = true;
			this->r_LblVal->Location = System::Drawing::Point(400, 105);
			this->r_LblVal->Name = L"r_LblVal";
			this->r_LblVal->Size = System::Drawing::Size(28, 13);
			this->r_LblVal->TabIndex = 25;
			this->r_LblVal->Text = L"1.00";
			// 
			// amplitude_lbl
			// 
			this->amplitude_lbl->AutoSize = true;
			this->amplitude_lbl->Location = System::Drawing::Point(41, 435);
			this->amplitude_lbl->Name = L"amplitude_lbl";
			this->amplitude_lbl->Size = System::Drawing::Size(53, 13);
			this->amplitude_lbl->TabIndex = 26;
			this->amplitude_lbl->Text = L"Amplitude";
			// 
			// g_LblVal
			// 
			this->g_LblVal->AutoSize = true;
			this->g_LblVal->Location = System::Drawing::Point(403, 145);
			this->g_LblVal->Name = L"g_LblVal";
			this->g_LblVal->Size = System::Drawing::Size(28, 13);
			this->g_LblVal->TabIndex = 27;
			this->g_LblVal->Text = L"1.00";
			// 
			// b_LblVal
			// 
			this->b_LblVal->AutoSize = true;
			this->b_LblVal->Location = System::Drawing::Point(403, 183);
			this->b_LblVal->Name = L"b_LblVal";
			this->b_LblVal->Size = System::Drawing::Size(28, 13);
			this->b_LblVal->TabIndex = 28;
			this->b_LblVal->Text = L"1.00";
			// 
			// frequency_LblVal
			// 
			this->frequency_LblVal->AutoSize = true;
			this->frequency_LblVal->Location = System::Drawing::Point(406, 396);
			this->frequency_LblVal->Name = L"frequency_LblVal";
			this->frequency_LblVal->Size = System::Drawing::Size(28, 13);
			this->frequency_LblVal->TabIndex = 29;
			this->frequency_LblVal->Text = L"4.00";
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(475, 582);
			this->Controls->Add(this->frequency_LblVal);
			this->Controls->Add(this->b_LblVal);
			this->Controls->Add(this->g_LblVal);
			this->Controls->Add(this->amplitude_lbl);
			this->Controls->Add(this->r_LblVal);
			this->Controls->Add(this->SpecStrength_LblVal);
			this->Controls->Add(this->frequency_Lbl);
			this->Controls->Add(this->B_Label);
			this->Controls->Add(this->G_Label);
			this->Controls->Add(this->R_Label);
			this->Controls->Add(this->SpecColor_Lbl);
			this->Controls->Add(this->SpecStrength_Lbl);
			this->Controls->Add(this->amplitude_LblVal);
			this->Controls->Add(this->trackBar_Amplitude_Component);
			this->Controls->Add(this->trackBar_Frequency_Component);
			this->Controls->Add(this->trackBar_B_Component);
			this->Controls->Add(this->trackBar_G_Component);
			this->Controls->Add(this->trackBar_R_Component);
			this->Controls->Add(this->trackBar_SpecStrength_Component);
			this->Controls->Add(this->checkBoxTintBlue);
			this->Controls->Add(this->checkBoxWireframeRender);
			this->Controls->Add(this->checkBoxScale);
			this->Controls->Add(this->checkBoxRotate);
			this->Controls->Add(this->checkBoxTranslate);
			this->Controls->Add(this->resetTransformBtn);
			this->Controls->Add(this->restLightPosBtn);
			this->Controls->Add(this->spaceSceneBtn);
			this->Controls->Add(this->waterSceneBtn);
			this->Controls->Add(this->transformBtn);
			this->Controls->Add(this->moveLightBtn);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_SpecStrength_Component))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_R_Component))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_G_Component))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_B_Component))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Frequency_Component))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Amplitude_Component))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void moveLightBtn_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		moveLight_Channel = moveLightBtn->Checked;
	}
	private: System::Void restLightPosBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		resetLight_Btn = true;
	}
	private: System::Void trackBar_SpecStrength_Component_Scroll(System::Object^ sender, System::EventArgs^ e) {
		trackBar_SpecStrength = trackBar_SpecStrength_Component->Value;
		SpecStrength_LblVal->Text = (trackBar_SpecStrength).ToString();
	}
	private: System::Void trackBar_R_Component_Scroll(System::Object^ sender, System::EventArgs^ e) {
		trackBar_R = trackBar_R_Component->Value / 100.0f ;
		r_LblVal->Text = (trackBar_R).ToString();
	}
	private: System::Void trackBar_G_Component_Scroll(System::Object^ sender, System::EventArgs^ e) {
		trackBar_G = trackBar_G_Component->Value / 100.0f;
		g_LblVal->Text = (trackBar_G).ToString();
	}
	private: System::Void trackBar_B_Component_Scroll(System::Object^ sender, System::EventArgs^ e) {
		trackBar_B = trackBar_B_Component->Value / 100.0f;
		b_LblVal->Text = (trackBar_B).ToString();
	}
	private: System::Void transformBtn_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		transform_Channel = transformBtn->Checked;
	}
	private: System::Void resetTransformBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		resetTransform_Btn = true;
	}
	private: System::Void checkBoxTranslate_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		RenderTranslate_Channel = checkBoxTranslate->Checked;
	}
	private: System::Void checkBoxRotate_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		RenderRotate_Channel = checkBoxRotate->Checked;
	}
	private: System::Void checkBoxScale_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		RenderScale_Channel = checkBoxScale->Checked;
	}
	private: System::Void waterSceneBtn_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		waterScene_Channel = waterSceneBtn->Checked;
	}
	private: System::Void trackBar_Frequency_Component_Scroll(System::Object^ sender, System::EventArgs^ e) {
		trackBar_Frequency = trackBar_Frequency_Component->Value / 100.0f;
		frequency_LblVal->Text = (trackBar_Frequency).ToString();
	}
	private: System::Void trackBar_Amplitude_Component_Scroll(System::Object^ sender, System::EventArgs^ e) {
		trackBar_Amplitude = trackBar_Amplitude_Component->Value / 100.0f;
		amplitude_LblVal->Text = (trackBar_Amplitude).ToString();
	}
	private: System::Void checkBoxWireframeRender_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		RenderWireframe_Channel = checkBoxWireframeRender->Checked;
	}
	private: System::Void checkBoxTintBlue_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		RenderTintBlue_Channel = checkBoxTintBlue->Checked;
	}
	private: System::Void spaceSceneBtn_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		spaceScene_Channel = spaceSceneBtn->Checked;
	}
};
}
