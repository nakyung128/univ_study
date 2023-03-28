import java.awt.EventQueue;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.BorderLayout;
import javax.swing.JTextField;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.ActionEvent;
import javax.swing.JTextArea;
import javax.swing.JLabel;
import java.awt.Font;

public class ServerFrame {

	private JFrame frame;
	private JTextField msgTf;
	private JTextArea textArea;

	ServerSocket serverSocket;
	Socket socket;
	DataInputStream dis;
	DataOutputStream dos;
	private JLabel lblNewLabel;
	private JTextField hostTf;
	private JButton btnNewButton;
	private JButton btnNewButton_1;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					ServerFrame window = new ServerFrame();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public ServerFrame() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	class ServerThread extends Thread {
		@Override
		public void run() {
			try {
				serverSocket = new ServerSocket(Integer.parseInt(hostTf.getText()));
				textArea.append("서버 소켓이 준비되었습니다... \n");
				textArea.append("클라이언트의 접속을 기다립니다... \n");
				socket = serverSocket.accept();
				textArea.append("상대방이 접속했습니다.\n");

				dis = new DataInputStream(socket.getInputStream());
				dos = new DataOutputStream(socket.getOutputStream());

				while (true) {
					String msg = dis.readUTF();
					textArea.append("[상대방]: " + msg + "\n");
					textArea.setCaretPosition(textArea.getText().length());
				}
			} catch (IOException e) {
				textArea.append("클라이언트가 나갔습니다.\n");
			}
		}
	}

	void sendMessage() {
		String msg = msgTf.getText();
		msgTf.setText("");
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
		frame = new JFrame("SERVER");
		frame.setBounds(100, 100, 389, 561);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		JPanel panel = new JPanel();
		frame.getContentPane().add(panel, BorderLayout.CENTER);
		panel.setLayout(null);

		msgTf = new JTextField();
		msgTf.setBounds(12, 491, 269, 23);
		panel.add(msgTf);
		msgTf.setColumns(10);

		JButton sendBtn = new JButton("SEND");
		sendBtn.setFont(new Font("a시월구일굴림2", Font.PLAIN, 12));
		sendBtn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				sendMessage();
			}
		});
		msgTf.addKeyListener(new KeyAdapter() {
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
		msgTf.requestFocus();
		sendBtn.setBounds(286, 491, 70, 23);
		panel.add(sendBtn);

		textArea = new JTextArea();
		textArea.setBounds(12, 46, 344, 435);
		textArea.setEditable(false);
		panel.add(textArea);

		lblNewLabel = new JLabel("PORT");
		lblNewLabel.setFont(new Font("a시월구일굴림2", Font.PLAIN, 12));
		lblNewLabel.setBounds(12, 18, 40, 15);
		panel.add(lblNewLabel);

		hostTf = new JTextField();
		hostTf.setBounds(55, 14, 106, 21);
		panel.add(hostTf);
		hostTf.setColumns(10);

		btnNewButton = new JButton("\uC811\uC18D");
		btnNewButton.setFont(new Font("a시월구일굴림1", Font.PLAIN, 12));
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {

				ServerThread serverThread = new ServerThread();
				serverThread.setDaemon(true);
				serverThread.start();
			}
		});
		btnNewButton.setBounds(212, 13, 70, 23);
		panel.add(btnNewButton);
		
		btnNewButton_1 = new JButton("\uD574\uC81C");
		btnNewButton_1.setFont(new Font("a시월구일굴림1", Font.PLAIN, 12));
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
		btnNewButton_1.setBounds(294, 13, 69, 23);
		panel.add(btnNewButton_1);

	}
}
