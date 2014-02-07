#pragma once
#include "WifibotClient.h"
#include "time.h"
//#include <thread>

#define DROITE x
#define GAUCHE y
namespace Wifibot {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/****************** VARIABLES ****************/

	CPoint direction;
	WifibotClient robot;

	int droite(0), gauche(0);

	SensorData capteurs;
	

	/*********************************************/

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public: Form1(void)
			{
				InitializeComponent();
			}

	protected:~Form1()
			{
				if (components)
					delete components;
			}

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  rbSimulateur;
	private: System::Windows::Forms::RadioButton^  rbRobot;
	private: System::Windows::Forms::Button^  btConnecter;
	private: System::Windows::Forms::Button^  btDeconnecter;
	private: System::Windows::Forms::Button^  btArriere;
	private: System::Windows::Forms::Button^  btStop;
	private: System::Windows::Forms::Button^  btAvant;
	private: System::Windows::Forms::Button^  btGauche;
	private: System::Windows::Forms::Button^  btDroite;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::WebBrowser^  webBrowser1;

	private: System::Windows::Forms::Label^  lbMoteurGauche;
	private: System::Windows::Forms::Label^  lbMoteurDroite;
	private: System::Windows::Forms::Label^  lbBatterie;
	private: System::Windows::Forms::Label^  lbIRGauche;
	private: System::Windows::Forms::Label^  lbIRDroite;

			 // Textes Moteur IR Batterie ect...
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;




	private: System::ComponentModel::IContainer^  components;


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->rbSimulateur = (gcnew System::Windows::Forms::RadioButton());
			this->rbRobot = (gcnew System::Windows::Forms::RadioButton());
			this->btConnecter = (gcnew System::Windows::Forms::Button());
			this->btDeconnecter = (gcnew System::Windows::Forms::Button());
			this->btArriere = (gcnew System::Windows::Forms::Button());
			this->btStop = (gcnew System::Windows::Forms::Button());
			this->btAvant = (gcnew System::Windows::Forms::Button());
			this->btGauche = (gcnew System::Windows::Forms::Button());
			this->btDroite = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
			this->lbMoteurGauche = (gcnew System::Windows::Forms::Label());
			this->lbMoteurDroite = (gcnew System::Windows::Forms::Label());
			this->lbBatterie = (gcnew System::Windows::Forms::Label());
			this->lbIRGauche = (gcnew System::Windows::Forms::Label());
			this->lbIRDroite = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->rbSimulateur);
			this->groupBox1->Controls->Add(this->rbRobot);
			this->groupBox1->Location = System::Drawing::Point(22, 477);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 39);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			// 
			// rbSimulateur
			// 
			this->rbSimulateur->AutoSize = true;
			this->rbSimulateur->Checked = true;
			this->rbSimulateur->Location = System::Drawing::Point(115, 16);
			this->rbSimulateur->Name = L"rbSimulateur";
			this->rbSimulateur->Size = System::Drawing::Size(74, 17);
			this->rbSimulateur->TabIndex = 1;
			this->rbSimulateur->TabStop = true;
			this->rbSimulateur->Text = L"Simulateur";
			this->rbSimulateur->UseVisualStyleBackColor = true;
			this->rbSimulateur->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->rbSimulateur->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyUp);
			// 
			// rbRobot
			// 
			this->rbRobot->AutoSize = true;
			this->rbRobot->Location = System::Drawing::Point(22, 16);
			this->rbRobot->Name = L"rbRobot";
			this->rbRobot->Size = System::Drawing::Size(54, 17);
			this->rbRobot->TabIndex = 0;
			this->rbRobot->Text = L"Robot";
			this->rbRobot->UseVisualStyleBackColor = true;
			this->rbRobot->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->rbRobot->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyUp);
			// 
			// btConnecter
			// 
			this->btConnecter->Location = System::Drawing::Point(55, 522);
			this->btConnecter->Name = L"btConnecter";
			this->btConnecter->Size = System::Drawing::Size(133, 54);
			this->btConnecter->TabIndex = 1;
			this->btConnecter->Text = L"Connecter";
			this->btConnecter->UseVisualStyleBackColor = true;
			this->btConnecter->Click += gcnew System::EventHandler(this, &Form1::btConnecter_Click);
			this->btConnecter->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->btConnecter->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyUp);
			// 
			// btDeconnecter
			// 
			this->btDeconnecter->Location = System::Drawing::Point(55, 585);
			this->btDeconnecter->Name = L"btDeconnecter";
			this->btDeconnecter->Size = System::Drawing::Size(133, 37);
			this->btDeconnecter->TabIndex = 2;
			this->btDeconnecter->Text = L"D�connecter";
			this->btDeconnecter->UseVisualStyleBackColor = true;
			this->btDeconnecter->Click += gcnew System::EventHandler(this, &Form1::btDeconnecter_Click);
			this->btDeconnecter->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->btDeconnecter->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyUp);
			// 
			// btArriere
			// 
			this->btArriere->Location = System::Drawing::Point(426, 579);
			this->btArriere->Name = L"btArriere";
			this->btArriere->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->btArriere->Size = System::Drawing::Size(99, 43);
			this->btArriere->TabIndex = 3;
			this->btArriere->Text = L"Arri�re";
			this->btArriere->UseVisualStyleBackColor = true;
			this->btArriere->Click += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			this->btArriere->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->btArriere->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyUp);
			this->btArriere->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btArriere_MouseDown);
			this->btArriere->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btArriere_MouseUp);
			// 
			// btStop
			// 
			this->btStop->Location = System::Drawing::Point(426, 533);
			this->btStop->Name = L"btStop";
			this->btStop->Size = System::Drawing::Size(99, 43);
			this->btStop->TabIndex = 4;
			this->btStop->Text = L"Stop";
			this->btStop->UseVisualStyleBackColor = true;
			this->btStop->Click += gcnew System::EventHandler(this, &Form1::btStop_Click);
			this->btStop->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->btStop->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyUp);
			// 
			// btAvant
			// 
			this->btAvant->Location = System::Drawing::Point(426, 487);
			this->btAvant->Name = L"btAvant";
			this->btAvant->Size = System::Drawing::Size(99, 43);
			this->btAvant->TabIndex = 5;
			this->btAvant->Text = L"Avant";
			this->btAvant->UseVisualStyleBackColor = true;
			this->btAvant->Click += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			this->btAvant->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->btAvant->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyUp);
			this->btAvant->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btAvant_MouseDown);
			this->btAvant->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btAvant_MouseUp);
			// 
			// btGauche
			// 
			this->btGauche->Location = System::Drawing::Point(321, 533);
			this->btGauche->Name = L"btGauche";
			this->btGauche->Size = System::Drawing::Size(99, 43);
			this->btGauche->TabIndex = 6;
			this->btGauche->Text = L"Gauche";
			this->btGauche->UseVisualStyleBackColor = true;
			this->btGauche->Click += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			this->btGauche->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->btGauche->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyUp);
			this->btGauche->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btGauche_MouseDown);
			this->btGauche->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btGauche_MouseUp);
			// 
			// btDroite
			// 
			this->btDroite->Location = System::Drawing::Point(531, 533);
			this->btDroite->Name = L"btDroite";
			this->btDroite->Size = System::Drawing::Size(99, 43);
			this->btDroite->TabIndex = 7;
			this->btDroite->Text = L"Droite";
			this->btDroite->UseVisualStyleBackColor = true;
			this->btDroite->Click += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			this->btDroite->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->btDroite->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyUp);
			this->btDroite->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btDroite_MouseDown);
			this->btDroite->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btDroite_MouseUp);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// webBrowser1
			// 
			this->webBrowser1->Location = System::Drawing::Point(3, 2);
			this->webBrowser1->MinimumSize = System::Drawing::Size(20, 20);
			this->webBrowser1->Name = L"webBrowser1";
			this->webBrowser1->Size = System::Drawing::Size(989, 479);
			this->webBrowser1->TabIndex = 8;
			this->webBrowser1->Url = (gcnew System::Uri(L"http://192.168.1.106", System::UriKind::Absolute));
			// 
			// lbMoteurGauche
			// 
			this->lbMoteurGauche->AutoSize = true;
			this->lbMoteurGauche->Location = System::Drawing::Point(813, 522);
			this->lbMoteurGauche->Name = L"lbMoteurGauche";
			this->lbMoteurGauche->Size = System::Drawing::Size(16, 13);
			this->lbMoteurGauche->TabIndex = 9;
			this->lbMoteurGauche->Text = L"---";
			// 
			// lbMoteurDroite
			// 
			this->lbMoteurDroite->AutoSize = true;
			this->lbMoteurDroite->Location = System::Drawing::Point(813, 543);
			this->lbMoteurDroite->Name = L"lbMoteurDroite";
			this->lbMoteurDroite->Size = System::Drawing::Size(16, 13);
			this->lbMoteurDroite->TabIndex = 10;
			this->lbMoteurDroite->Text = L"---";
			// 
			// lbBatterie
			// 
			this->lbBatterie->AutoSize = true;
			this->lbBatterie->Location = System::Drawing::Point(813, 502);
			this->lbBatterie->Name = L"lbBatterie";
			this->lbBatterie->Size = System::Drawing::Size(16, 13);
			this->lbBatterie->TabIndex = 11;
			this->lbBatterie->Text = L"---";
			// 
			// lbIRGauche
			// 
			this->lbIRGauche->AutoSize = true;
			this->lbIRGauche->Location = System::Drawing::Point(813, 563);
			this->lbIRGauche->Name = L"lbIRGauche";
			this->lbIRGauche->Size = System::Drawing::Size(16, 13);
			this->lbIRGauche->TabIndex = 12;
			this->lbIRGauche->Text = L"---";
			// 
			// lbIRDroite
			// 
			this->lbIRDroite->AutoSize = true;
			this->lbIRDroite->Location = System::Drawing::Point(813, 585);
			this->lbIRDroite->Name = L"lbIRDroite";
			this->lbIRDroite->Size = System::Drawing::Size(16, 13);
			this->lbIRDroite->TabIndex = 13;
			this->lbIRDroite->Text = L"---";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(721, 503);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(46, 13);
			this->label2->TabIndex = 15;
			this->label2->Text = L"Batterie ";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(721, 522);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(81, 13);
			this->label3->TabIndex = 16;
			this->label3->Text = L"Moteur Gauche";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(721, 543);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(65, 13);
			this->label4->TabIndex = 17;
			this->label4->Text = L"Moteur Droit";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(721, 563);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(59, 13);
			this->label5->TabIndex = 18;
			this->label5->Text = L"IR Gauche";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(721, 585);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(43, 13);
			this->label6->TabIndex = 19;
			this->label6->Text = L"IR Droit";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(996, 627);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->lbIRDroite);
			this->Controls->Add(this->lbIRGauche);
			this->Controls->Add(this->lbBatterie);
			this->Controls->Add(this->lbMoteurDroite);
			this->Controls->Add(this->lbMoteurGauche);
			this->Controls->Add(this->webBrowser1);
			this->Controls->Add(this->btDroite);
			this->Controls->Add(this->btGauche);
			this->Controls->Add(this->btAvant);
			this->Controls->Add(this->btStop);
			this->Controls->Add(this->btArriere);
			this->Controls->Add(this->btDeconnecter);
			this->Controls->Add(this->btConnecter);
			this->Controls->Add(this->groupBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyUp);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion  Windows Form Designer generated code

//Connecte le robot, ou reinitialise la connection si on est deja connect�s
private: System::Void btConnecter_Click(System::Object^  sender, System::EventArgs^  e)
		{
					if(rbSimulateur->Checked)
					{								
						//robot.DisconnectRobot();

						char ip[20]="127.0.0.1";		//localhost
						int port=15020;					//port TCP

						robot.ConnectToRobot(ip,port);	//connection
					}
					
					else if(rbRobot->Checked)
					{								
						//robot.DisconnectRobot();

						char ip[20]="192.168.1.106";		//localhost
						int port=15010;					//port TCP

						robot.ConnectToRobot(ip,port);	//connection
					}

		}

private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e)
		{
			timer1->Interval=400;		// Quand un boutton est pr�ss�, le timer renvoie la consigne toutes les 400ms	 
		}

private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e)
		 {
						 	robot.SendConsigne(direction);
							robot.GetSensorData(&capteurs);

							lbBatterie->Text =		"" +capteurs.BatVoltage;
							lbMoteurDroite->Text =	"" +capteurs.SpeedFrontRight;
							lbMoteurGauche->Text =	"" +capteurs.SpeedFrontLeft;
							lbIRDroite->Text =		"" +capteurs.IRRight;
							lbIRGauche->Text =		"" +capteurs.IRLeft;
		 }

private: System::Void btStop_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {			
				
				direction.y=0;
				direction.x=0;
		 }
private: System::Void btDeconnecter_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			robot.DisconnectRobot();
			timer1->Stop();
		 }

private: System::Void btDroite_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			gauche=(int) (gauche*1.4);
			droite=(int) (droite/1.4);								
			direction.GAUCHE=gauche;
			direction.DROITE=droite;
			timer1->Start();
		 }
private: System::Void btDroite_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			 timer1->Stop();
		 }

private: System::Void btGauche_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			gauche=(int) (gauche/1.4);
			droite=(int) (droite*1.4);								
			direction.GAUCHE=gauche;
			direction.DROITE=droite;
			timer1->Start();
		 }
private: System::Void btGauche_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			 timer1->Stop();
		 }

private: System::Void btArriere_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			 droite =-20;
			 gauche= -20;
			 direction.GAUCHE=gauche;
			 direction.DROITE=droite;
			 timer1->Start();
		 }
private: System::Void btArriere_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			 timer1->Stop();
		 }

private: System::Void btAvant_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			 droite =20;
			 gauche= 20;
			 direction.GAUCHE=gauche;
			 direction.DROITE=droite;
			 timer1->Start();
		 }
private: System::Void btAvant_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			 timer1->Stop();
		 }

private: System::Void btStop_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			timer1->Stop();
		 }

private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
		 {
			switch (e->KeyCode)
            {
                case Keys::Z :	  gauche=20;
								  droite=20;
								  direction.GAUCHE=gauche;
								  direction.DROITE=droite;
								  timer1->Start();
								  break;
               
				case Keys::Q :				
								  direction.GAUCHE=(int)(gauche/1.4);
								  direction.DROITE=(int)(droite*1.4);
								  timer1->Start();
								  break;
                
				case Keys::S :	  droite=-20;
								  gauche=-20;
								  direction.GAUCHE=gauche;
								  direction.DROITE=droite;
								  timer1->Start();
								  break;

                case Keys::D :	  direction.GAUCHE=(int) (gauche*1.4);
								  direction.DROITE=(int) (droite/1.4);
								  timer1->Start();
								  break;

				case Keys::Space: gauche=0;
								  droite=0;									
								  direction.GAUCHE=gauche;
								  direction.DROITE=droite;

				default :;	

		}



			
			switch (e->KeyCode)
            {
                case Keys::Z :	  gauche=20;
								  droite=20;
								  direction.GAUCHE=gauche;
								  direction.DROITE=droite;
								  timer1->Start();
								  break;
               
				case Keys::Q :				
								  direction.GAUCHE=(int)(gauche/1.4);
								  direction.DROITE=(int)(droite*1.4);
								  timer1->Start();
								  break;
                
				case Keys::S :	  droite=-20;
								  gauche=-20;
								  direction.GAUCHE=gauche;
								  direction.DROITE=droite;
								  timer1->Start();
								  break;

                case Keys::D :	  direction.GAUCHE=(int) (gauche*1.4);
								  direction.DROITE=(int) (droite/1.4);
								  timer1->Start();
								  break;

				case Keys::Space: gauche=0;
								  droite=0;									
								  direction.GAUCHE=gauche;
								  direction.DROITE=droite;

				default :;	

		}

		/*
                if(e->KeyCode==Keys::Z)
				{
					gauche=20;
					droite=20;
					direction.GAUCHE=gauche;
					direction.DROITE=droite;
					timer1->Start();
				}
               
                if(e->KeyCode==Keys::Q)
				{				
					direction.GAUCHE=(int)(gauche/1.4);
					direction.DROITE=(int)(droite*1.4);
					timer1->Start();
				}

                if(e->KeyCode==Keys::S)
				{			 
					droite=-20;
					gauche=-20;
					direction.GAUCHE=gauche;
					direction.DROITE=droite;
					timer1->Start();
				}

                if(e->KeyCode==Keys::D)
				{	  
					direction.GAUCHE=(int) (gauche*1.4);
					direction.DROITE=(int) (droite/1.4);
					timer1->Start();
				}

                if(e->KeyCode==Keys::Space)
				{
					gauche=0;
					droite=0;									
					direction.GAUCHE=gauche;
					direction.DROITE=droite;
				}*/
		 }
private: System::Void Form1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
		 {
			//if(chkAvanceAuto->ThreeState==false)			//Si la checkbox est d�coch�e	
				//timer1->Stop();
			
				direction.y=gauche;								//On a relach� le bouton, on reprend la direction precedente (avant ou arriere)
				direction.x=droite;
		 }

};
}

