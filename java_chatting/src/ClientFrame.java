import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.awt.event.ActionEvent;
import javax.swing.JLabel;
import java.awt.Font;
import javax.swing.JPanel;

public class ClientFrame {

	private JFrame frmClient;
	private JTextField textField;
	private JTextArea textArea;
	Socket socket;
	DataInputStream dis;
	DataOutputStream dos;
	private JTextField hostTf;
	private JTextField ipTf;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					ClientFrame window = new ClientFrame();
					window.frmClient.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public ClientFrame() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */

	class ClientThread extends Thread {
		@Override
		public void run() {
			try {
				socket = new Socket(ipTf.getText(), Integer.parseInt(hostTf.getText()));
				textArea.append("서버에 접속됐습니다.\n");
				InputStream is = socket.getInputStream();
				OutputStream os = socket.getOutputStream();

				dis = new DataInputStream(is);
				dos = new DataOutputStream(os);

				while (true) {
					String msg = dis.readUTF();
					textArea.append("[상대방]: " + msg + "\n");
					textArea.setCaretPosition(textArea.getText().length());
				}
			} catch (UnknownHostException e) {
				textArea.append("서버 주소가 이상합니다.\n");
			} catch (IOException e) {
				textArea.append("서버와 연결이 끊겼습니다.\n");
			}
		}

	}

	void sendMessage() {
		String msg = textField.getText();
		textField.setText("");
		textArea.append("[나]: " + msg + "\n");
		textArea.setCaretPosition(textArea.getText().length());

		Thread t = new Thread() {
			@Override
			public void run() {
				try {
					dos.writeUTF(msg);
					dos.flush();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		};
		t.start();
	}

	private void initialize() {
		frmClient = new JFrame();
		frmClient.setTitle("CLIENT");
		frmClient.setBounds(100, 100, 389, 561);
		frmClient.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frmClient.getContentPane().setLayout(null);

		textArea = new JTextArea();
		textArea.setBounds(12, 44, 357, 439);
		frmClient.getContentPane().add(textArea);

		textField = new JTextField();
		textField.setBounds(12, 493, 280, 21);
		frmClient.getContentPane().add(textField);
		textField.setColumns(10);

		JButton sendBtn = new JButton("SEND");
		sendBtn.setFont(new Font("a시월구일굴림2", Font.PLAIN, 12));

		textField.requestFocus();

		textField.addKeyListener(new KeyAdapter() {
			@Override
			public void keyPressed(KeyEvent e) {
				super.keyPressed(e);

				int keyCode = e.getKeyCode();
				switch (keyCode) {
				case KeyEvent.VK_ENTER:
					sendMessage();
					break;
				}
			}
		});

		sendBtn.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				sendMessage();
			}
		});

		textField.requestFocus();

		sendBtn.setBounds(297, 492, 72, 23);
		frmClient.getContentPane().add(sendBtn);

		hostTf = new JTextField();
		hostTf.setBounds(166, 13, 79, 21);
		frmClient.getContentPane().add(hostTf);
		hostTf.setColumns(10);

		ipTf = new JTextField();
		ipTf.setBounds(29, 13, 96, 21);
		frmClient.getContentPane().add(ipTf);
		ipTf.setColumns(10);

		JLabel lblNewLabel = new JLabel("IP");
		lblNewLabel.setFont(new Font("a시월구일굴림2", Font.PLAIN, 12));
		lblNewLabel.setBounds(12, 16, 17, 15);
		frmClient.getContentPane().add(lblNewLabel);

		JLabel lblNewLabel_1 = new JLabel("PORT");
		lblNewLabel_1.setFont(new Font("a시월구일굴림2", Font.PLAIN, 12));
		lblNewLabel_1.setBounds(129, 16, 39, 15);
		frmClient.getContentPane().add(lblNewLabel_1);

		JButton btnNewButton = new JButton("\uC811\uC18D");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ClientThread clientThread = new ClientThread();
				clientThread.setDaemon(true);
				clientThread.start();
			}
		});

		btnNewButton.setFont(new Font("a시월구일굴림1", Font.PLAIN, 11));
		btnNewButton.setBounds(250, 13, 60, 23);
		frmClient.getContentPane().add(btnNewButton);
		
		JButton btnNewButton_1 = new JButton("\uD574\uC81C");
		btnNewButton_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					socket.close();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		btnNewButton_1.setFont(new Font("a시월구일굴림1", Font.PLAIN, 11));
		btnNewButton_1.setBounds(309, 13, 60, 23);
		frmClient.getContentPane().add(btnNewButton_1);

	}
}
