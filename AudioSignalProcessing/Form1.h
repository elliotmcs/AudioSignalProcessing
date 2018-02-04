#pragma once

#include "stdafx.h"
#include "FileHandler.h"
#include "WavReader.h"
#include "FourierTransform.h"
#include "DialogForm.h"
#include "AudioFilters.h"
#include "ComplexArray.h"

namespace CppCLR_WinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	
	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  audioFileToolStripMenuItem;
	public: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::Label^  label2;

	private: System::Windows::Forms::PictureBox^  pictureBox_time;
	private: System::Windows::Forms::PictureBox^  pictureBox_freq;
	private: System::Windows::Forms::PictureBox^  pictureBox_filter_overlay;

	
	private: 
		Complex * wav_time;
		Complex * wav_freq;
		int waveform_samples;
		int sample_rate;
		ArrayList ^active_filters = gcnew ArrayList();
		ArrayList ^filter_boxes = gcnew ArrayList();
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::MenuStrip^  menuStrip2;
	private: System::Windows::Forms::ToolStripMenuItem^  addToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  lowpassFilterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  heighpassFilterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bandpassFilterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bandrejectFilterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  combFilterToolStripMenuItem;









	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->audioFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->menuStrip2 = (gcnew System::Windows::Forms::MenuStrip());
			this->addToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lowpassFilterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->heighpassFilterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bandpassFilterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bandrejectFilterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->combFilterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->menuStrip1->SuspendLayout();
			this->panel1->SuspendLayout();
			this->menuStrip2->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->helpToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(704, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->openToolStripMenuItem,
					this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->audioFileToolStripMenuItem });
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			this->openToolStripMenuItem->Text = L"Open";
			// 
			// audioFileToolStripMenuItem
			// 
			this->audioFileToolStripMenuItem->Name = L"audioFileToolStripMenuItem";
			this->audioFileToolStripMenuItem->Size = System::Drawing::Size(127, 22);
			this->audioFileToolStripMenuItem->Text = L"Audio File";
			this->audioFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openAudioFileToolClicked);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->CheckOnClick = true;
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolClicked);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(53, 63);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(104, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"filename placeholder";
			this->label1->Visible = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(53, 216);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(70, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Audio Effects";
			this->label2->Visible = false;
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->menuStrip2);
			this->panel1->Location = System::Drawing::Point(56, 232);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(597, 197);
			this->panel1->TabIndex = 8;
			this->panel1->Visible = false;
			// 
			// menuStrip2
			// 
			this->menuStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->addToolStripMenuItem });
			this->menuStrip2->Location = System::Drawing::Point(0, 0);
			this->menuStrip2->Name = L"menuStrip2";
			this->menuStrip2->Size = System::Drawing::Size(595, 24);
			this->menuStrip2->TabIndex = 0;
			this->menuStrip2->Text = L"menuStrip2";
			// 
			// addToolStripMenuItem
			// 
			this->addToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->lowpassFilterToolStripMenuItem,
					this->heighpassFilterToolStripMenuItem, this->bandpassFilterToolStripMenuItem, this->bandrejectFilterToolStripMenuItem, this->combFilterToolStripMenuItem
			});
			this->addToolStripMenuItem->Name = L"addToolStripMenuItem";
			this->addToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->addToolStripMenuItem->Text = L"Add";
			// 
			// lowpassFilterToolStripMenuItem
			// 
			this->lowpassFilterToolStripMenuItem->Name = L"lowpassFilterToolStripMenuItem";
			this->lowpassFilterToolStripMenuItem->Size = System::Drawing::Size(159, 22);
			this->lowpassFilterToolStripMenuItem->Text = L"Lowpass Filter";
			this->lowpassFilterToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openLPFilterDialog);
			// 
			// heighpassFilterToolStripMenuItem
			// 
			this->heighpassFilterToolStripMenuItem->Name = L"heighpassFilterToolStripMenuItem";
			this->heighpassFilterToolStripMenuItem->Size = System::Drawing::Size(159, 22);
			this->heighpassFilterToolStripMenuItem->Text = L"Highpass Filter";
			this->heighpassFilterToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openHPFilterDialog);
			// 
			// bandpassFilterToolStripMenuItem
			// 
			this->bandpassFilterToolStripMenuItem->Name = L"bandpassFilterToolStripMenuItem";
			this->bandpassFilterToolStripMenuItem->Size = System::Drawing::Size(159, 22);
			this->bandpassFilterToolStripMenuItem->Text = L"Bandpass Filter";
			this->bandpassFilterToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openBPFilterDialog);
			// 
			// bandrejectFilterToolStripMenuItem
			// 
			this->bandrejectFilterToolStripMenuItem->Name = L"bandrejectFilterToolStripMenuItem";
			this->bandrejectFilterToolStripMenuItem->Size = System::Drawing::Size(159, 22);
			this->bandrejectFilterToolStripMenuItem->Text = L"Bandreject Filter";
			this->bandrejectFilterToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openBRFilterDialog);
			// 
			// combFilterToolStripMenuItem
			// 
			this->combFilterToolStripMenuItem->Name = L"combFilterToolStripMenuItem";
			this->combFilterToolStripMenuItem->Size = System::Drawing::Size(159, 22);
			this->combFilterToolStripMenuItem->Text = L"Comb Filter";
			this->combFilterToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openCMBFilterDialog);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(56, 80);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(597, 133);
			this->tabControl1->TabIndex = 9;
			this->tabControl1->Visible = false;
			// 
			// tabPage1
			// 
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(589, 107);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Time Domain";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(589, 107);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Frequency Domain";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(704, 441);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->menuStrip2->ResumeLayout(false);
			this->menuStrip2->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		void exitToolClicked(Object ^ sender, EventArgs ^ e) {
			exit(0);
		}

		void openAudioFileToolClicked(Object ^ sender, EventArgs ^ e) {
			
			System::String^ filename;

			OpenFileDialog^ openFileDialog = gcnew System::Windows::Forms::OpenFileDialog();

			openFileDialog->InitialDirectory = "c:\\";
			openFileDialog->Filter = "wav files (*.wav)|*.wav|All files (*.*)|*.*";
			openFileDialog->FilterIndex = 2;
			openFileDialog->RestoreDirectory = true;
			if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				filename = openFileDialog->FileName;
				this->label1->Text = filename;
				char * str = (char *)(void *)Marshal::StringToHGlobalAnsi(filename);
				//TODO: Error checks
				WavReader *wav_r = new WavReader(str);
				
				vector<uint32_t> data = wav_r->get_data();

				int m = ceil(log2(data.size()));
				waveform_samples = pow(2, m);
				sample_rate = (wav_r->get_SampleRate());

				wav_time = (Complex *)malloc(waveform_samples * sizeof(Complex));
				wav_freq = (Complex *)malloc(waveform_samples * sizeof(Complex));

				for (int i = 0; i < waveform_samples; i++) {
					if (i < data.size()) {
						int val = (int)data[i];
						val = (val > pow(2, wav_r->get_BitsPerSample() - 1)) ?
							val - pow(2, wav_r->get_BitsPerSample()) : val;
						wav_time[i] = Complex(val, 0);
						wav_freq[i] = Complex(val, 0);
					}
					else {
						wav_time[i] = Complex(0, 0);
						wav_freq[i] = Complex(0, 0);
					}
				}
				FourierTransform::fft(wav_freq, waveform_samples);

				delete wav_r;

				pictureBox_time = gcnew System::Windows::Forms::PictureBox();
				this->pictureBox_time->Location = System::Drawing::Point(0, 0);
				this->pictureBox_time->Name = L"pictureBox_time";
				this->pictureBox_time->Size = System::Drawing::Size(597, 100);
				this->pictureBox_time->TabIndex = 6;
				this->pictureBox_time->TabStop = false;
				this->pictureBox_time->Visible = true;
				// Connect the Paint event of the PictureBox to the event handler method.
				pictureBox_time->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pictureBox_time_Paint);

				pictureBox_freq = gcnew System::Windows::Forms::PictureBox();
				this->pictureBox_freq->Location = System::Drawing::Point(0, 0);
				this->pictureBox_freq->Name = L"pictureBox_freq";
				this->pictureBox_freq->Size = System::Drawing::Size(597, 100);
				this->pictureBox_freq->TabIndex = 8;
				this->pictureBox_freq->TabStop = false;
				// Connect the Paint event of the PictureBox to the event handler method.
				pictureBox_freq->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pictureBox_freq_Paint);

				// Add the PictureBox control to the Form.
				this->Controls->Add(pictureBox_time);
				this->Controls->Add(pictureBox_freq);
				pictureBox_time->Parent = tabPage1;
				pictureBox_freq->Parent = tabPage2;

				this->tabControl1->Visible = true;
				this->panel1->Visible = true;
				this->label1->Visible = true;
				this->label2->Visible = true;
				this->tabControl1->Visible = true;
				this->tabControl1->SelectedIndex = 0;
			}
			
		}

		void pictureBox_time_Paint(Object^ /*sender*/, System::Windows::Forms::PaintEventArgs^ e)
		{
			// Create a local version of the graphics object for the PictureBox.
			Graphics^ g = e->Graphics;
			float half_height = (float)pictureBox_time->Height / 2.0;
			float increments = (float)pictureBox_time->Width / (float)waveform_samples;
			float max_amp = -float::MaxValue;
			for (int i = 0; i < waveform_samples; i++) {
				if (wav_time[i].real() > max_amp) {
					max_amp = wav_time[i].real();
				}
			}
			float height_ratio = pictureBox_time->Height / (2 * max_amp);
			for (int i = 0; i < waveform_samples - 1; i++) {
				g->DrawLine(System::Drawing::Pens::Black, i*increments, half_height + wav_time[i].real()*height_ratio, (i + 1)*increments, half_height + wav_time[i + 1].real()*height_ratio);
			}
			
			//g->DrawLine(System::Drawing::Pens::Red, pictureBox_time->Left, pictureBox_time->Top,
				//pictureBox_time->Right, pictureBox_time->Bottom);
		}

		void pictureBox_freq_Paint(Object^ /*sender*/, System::Windows::Forms::PaintEventArgs^ e)
		{
			System::Diagnostics::Debug::WriteLine("Painting freq");
			// Create a local version of the graphics object for the PictureBox.
			Graphics^ g = e->Graphics;
			float half_height = (float)pictureBox_freq->Height / 2.0;
			float increments = (float)pictureBox_freq->Width / (float)waveform_samples;
			float max_amp = -float::MaxValue;
			for (int i = 0; i < waveform_samples; i++) {
				if (wav_freq[i].real() > max_amp) {
					max_amp = wav_freq[i].real();
				}
			}
			float height_ratio = pictureBox_freq->Height / (2 * max_amp);
			for (int i = 0; i < waveform_samples - 1; i++) {
				g->DrawLine(System::Drawing::Pens::Black, i*increments, half_height + wav_freq[i].real()*height_ratio, (i + 1)*increments, half_height + wav_freq[i + 1].real()*height_ratio);
			}

			
			float height = pictureBox_freq->Height;
			//float increments = (float)pictureBox_time->Width / (float)waveform_samples;
			int num_filters = active_filters->Count;
			System::Diagnostics::Debug::WriteLine(active_filters->Count);
			for (int k = 0; k < num_filters; k++) {
				ComplexArray ^curr_filter = safe_cast<ComplexArray ^>(active_filters[k]);
				Complex* curr_filter_a = curr_filter->c_array;
				Pen ^p = Pens::Blue;
				switch (k) {
				case 0:
					p = Pens::Red;
					break;
				case 1:
					p = Pens::Green;
					break;
				case 2:
					p = Pens::Yellow;
					break;
				case 3:
					p = Pens::Purple;
					break;
				case 4:
					p = Pens::Lavender;
					break;
				case 5:
					p = Pens::Magenta;
					break;
				case 6:
					p = Pens::Aquamarine;
					break;
				}
				for (int i = 0; i < waveform_samples - 1; i++) {
					g->DrawLine(p, i*increments, half_height - (height / 2) * abs(curr_filter_a[i]), (i + 1)*increments, half_height - (height / 2) * abs(curr_filter_a[i + 1]));
				}
			}
			
		}


		// Filter dialog: variables[0] = cutoff/cutoff1/delay, variables[1] = falloff/amplitude, variables[2] = cutoff2
		void openLPFilterDialog(Object ^ sender, EventArgs ^ e) {
			int variables[2] = { -1, -1 };
			CppCLR_WinformsProjekt2::DialogForm ^df = gcnew CppCLR_WinformsProjekt2::DialogForm(sample_rate, waveform_samples, 0, variables);
			if(df->ShowDialog() == System::Windows::Forms::DialogResult::OK){
				if (variables[0] != -1 && variables[1] != -1) {
					applyLPFilter(variables[0], variables[1]);
				}
			}
		}
		void openHPFilterDialog(Object ^ sender, EventArgs ^ e) {
			int variables[2] = { -1, -1 };
			CppCLR_WinformsProjekt2::DialogForm ^df = gcnew CppCLR_WinformsProjekt2::DialogForm(sample_rate, waveform_samples, 1, variables);
			if (df->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				if (variables[0] != -1 && variables[1] != -1) {
					applyHPFilter(variables[0], variables[1]);
				}
			}
		}
		void openBPFilterDialog(Object ^ sender, EventArgs ^ e) {
			int variables[3] = { -1, -1, -1};
			CppCLR_WinformsProjekt2::DialogForm ^df = gcnew CppCLR_WinformsProjekt2::DialogForm(sample_rate, waveform_samples, 2, variables);
			if (df->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				if (variables[0] != -1 && variables[1] != -1 && variables[2] != -1) {
					applyBPFilter(variables[0], variables[2], variables[1]);
				}
			}
		}
		void openBRFilterDialog(Object ^ sender, EventArgs ^ e) {
			int variables[3] = { -1, -1, -1 };
			CppCLR_WinformsProjekt2::DialogForm ^df = gcnew CppCLR_WinformsProjekt2::DialogForm(sample_rate, waveform_samples, 3, variables);
			if (df->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				if (variables[0] != -1 && variables[1] != -1) {
					applyBRFilter(variables[0], variables[2], variables[1]);
				}
			}
		}
		void openCMBFilterDialog(Object ^ sender, EventArgs ^ e) {
			int variables[2] = { -1, -1 };
			CppCLR_WinformsProjekt2::DialogForm ^df = gcnew CppCLR_WinformsProjekt2::DialogForm(sample_rate, waveform_samples, 4, variables);
			if (df->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				if (variables[0] != -1 && variables[1] != -1) {
					applyCMBFilter(variables[0], variables[1]);
				}
			}
		}

	public:
		void applyLPFilter(int cutoff, int falloff) {
			Complex *lpr = AudioFilters::lowpass_magnitude_response(this->sample_rate, this->waveform_samples, cutoff, falloff);
			ComplexArray ^lpr_a = gcnew ComplexArray(lpr, this->waveform_samples);
			active_filters->Add(lpr_a);
			this->pictureBox_freq->Invalidate();
			PictureBox ^filter_box = gcnew PictureBox();
			filter_box->Location = System::Drawing::Point(3 + (153 * filter_boxes->Count), 27);
			filter_box->Name = L"filter_box_" + filter_boxes->Count;
			filter_box->Size = System::Drawing::Size(100, 50);
			filter_box->TabIndex = 10;
			filter_box->TabStop = false;
			filter_box->BackColor = Color::Bisque;
			this->panel1->Controls->Add(filter_box);

			if (filter_boxes->Count != 1) {
				
				PictureBox ^arrow_box = gcnew PictureBox();
				arrow_box->Location = System::Drawing::Point(3 + (103 * filter_boxes->Count), 27);
				arrow_box->Name = L"arrow_box_" + filter_boxes->Count;
				arrow_box->Size = System::Drawing::Size(50, 50);
				arrow_box->TabIndex = 10;
				arrow_box->TabStop = false;
				
				this->panel1->Controls->Add(arrow_box);
			}
			filter_boxes->Add(filter_box);
		}
		void applyHPFilter(int cutoff, int falloff) {
			Complex *hpr = AudioFilters::highpass_magnitude_response(this->sample_rate, this->waveform_samples, cutoff, falloff);
			ComplexArray ^hpr_a = gcnew ComplexArray(hpr, this->waveform_samples);
			active_filters->Add(hpr_a);
			this->pictureBox_freq->Invalidate();
			PictureBox ^filter_box = gcnew PictureBox();
			filter_box->Location = System::Drawing::Point(3 + (153 * filter_boxes->Count), 27);
			filter_box->Name = L"filter_box_" + filter_boxes->Count;
			filter_box->Size = System::Drawing::Size(100, 50);
			filter_box->TabIndex = 10;
			filter_box->TabStop = false;
			filter_box->BackColor = Color::Bisque;
			this->panel1->Controls->Add(filter_box);

			if (filter_boxes->Count != 1) {
				PictureBox ^arrow_box = gcnew PictureBox();
				arrow_box->Location = System::Drawing::Point(3 + (103 * filter_boxes->Count), 27);
				arrow_box->Name = L"arrow_box_" + filter_boxes->Count;
				arrow_box->Size = System::Drawing::Size(50, 50);
				arrow_box->TabIndex = 10;
				arrow_box->TabStop = false;
				arrow_box->ImageLocation = L"Resources/arrow.png";
				this->panel1->Controls->Add(arrow_box);
			}
			filter_boxes->Add(filter_box);
		}
		void applyBPFilter(int cutoff1, int cutoff2, int falloff) {
			Complex *bpr = AudioFilters::bandpass_magnitude_response(this->sample_rate, this->waveform_samples, cutoff1, cutoff2, falloff);
			ComplexArray ^bpr_a = gcnew ComplexArray(bpr, this->waveform_samples);
			active_filters->Add(bpr_a);
			this->pictureBox_freq->Invalidate();
			PictureBox ^filter_box = gcnew PictureBox();
			filter_box->Location = System::Drawing::Point(3 + (153 * filter_boxes->Count), 27);
			filter_box->Name = L"filter_box_" + filter_boxes->Count;
			filter_box->Size = System::Drawing::Size(100, 50);
			filter_box->TabIndex = 10;
			filter_box->TabStop = false;
			filter_box->BackColor = Color::Bisque;
			this->panel1->Controls->Add(filter_box);

			if (filter_boxes->Count != 1) {
				PictureBox ^arrow_box = gcnew PictureBox();
				arrow_box->Location = System::Drawing::Point(3 + (103 * filter_boxes->Count), 27);
				arrow_box->Name = L"arrow_box_" + filter_boxes->Count;
				arrow_box->Size = System::Drawing::Size(50, 50);
				arrow_box->TabIndex = 10;
				arrow_box->TabStop = false;
				arrow_box->ImageLocation = L"Resources/arrow.png";
				this->panel1->Controls->Add(arrow_box);
			}
			filter_boxes->Add(filter_box);

		}
		void applyBRFilter(int cutoff1, int cutoff2, int falloff) {
			Complex *brr = AudioFilters::bandreject_magnitude_response(this->sample_rate, this->waveform_samples, cutoff1, cutoff2, falloff);
			ComplexArray ^brr_a = gcnew ComplexArray(brr, this->waveform_samples);
			active_filters->Add(brr_a);
			this->pictureBox_freq->Invalidate();
			PictureBox ^filter_box = gcnew PictureBox();
			filter_box->Location = System::Drawing::Point(3 + (153 * filter_boxes->Count), 27);
			filter_box->Name = L"filter_box_" + filter_boxes->Count;
			filter_box->Size = System::Drawing::Size(100, 50);
			filter_box->TabIndex = 10;
			filter_box->TabStop = false;
			filter_box->BackColor = Color::Bisque;
			this->panel1->Controls->Add(filter_box);

			if (filter_boxes->Count != 1) {
				PictureBox ^arrow_box = gcnew PictureBox();
				arrow_box->Location = System::Drawing::Point(3 + (103 * filter_boxes->Count), 27);
				arrow_box->Name = L"arrow_box_" + filter_boxes->Count;
				arrow_box->Size = System::Drawing::Size(50, 50);
				arrow_box->TabIndex = 10;
				arrow_box->TabStop = false;
				arrow_box->ImageLocation = L"Resources/arrow.png";
				this->panel1->Controls->Add(arrow_box);
			}
			filter_boxes->Add(filter_box);
		}
		void applyCMBFilter(int delay, int amp) {
			Complex *cr = AudioFilters::comb_magnitude_response(this->sample_rate, this->waveform_samples, delay, amp);
			ComplexArray ^cr_a = gcnew ComplexArray(cr, this->waveform_samples);
			active_filters->Add(cr_a);
			this->pictureBox_freq->Invalidate();
			PictureBox ^filter_box = gcnew PictureBox();
			filter_box->Location = System::Drawing::Point(3 + (153 * filter_boxes->Count), 27);
			filter_box->Name = L"filter_box_" + filter_boxes->Count;
			filter_box->Size = System::Drawing::Size(100, 50);
			filter_box->TabIndex = 10;
			filter_box->TabStop = false;
			filter_box->BackColor = Color::Bisque;
			this->panel1->Controls->Add(filter_box);

			if (filter_boxes->Count != 1) {
				PictureBox ^arrow_box = gcnew PictureBox();
				arrow_box->Location = System::Drawing::Point(3 + (103 * filter_boxes->Count), 27);
				arrow_box->Name = L"arrow_box_" + filter_boxes->Count;
				arrow_box->Size = System::Drawing::Size(50, 50);
				arrow_box->TabIndex = 10;
				arrow_box->TabStop = false;
				arrow_box->ImageLocation = L"Resources/arrow.png";
				this->panel1->Controls->Add(arrow_box);
			}
			filter_boxes->Add(filter_box);
		}
#pragma endregion
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
}
};
}
