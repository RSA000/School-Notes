//
//  pizzaView.swift
//  rustic_admin
//
//  Created by Richard Andison on 2022-12-11.
//

import SwiftUI
import CodeScanner
import Firebase

struct pizzaView: View {
    @EnvironmentObject var dataManager: DataManager
    @State var scannedCode: String = "Scanned email will appear here"
    @State var points = 0
    @State var scanned = false
    @State var isPresentingScanner = false
    @State var errorMsg = ""
    @State var success = ""

    
    // Scans for QR code
    var scannerSheet : some View{
            CodeScannerView(
                codeTypes: [.qr],
                completion: {result in
                    if case let .success(code) = result {
                        self.scannedCode = code.string
                        self.isPresentingScanner = false
                        dataManager.fetchPoints(email: scannedCode)
                        
                        // Checking if user email exists
                        var result_count = 0
                        let db = Firestore.firestore()
                        let ref = db.collection("users").whereField("email", isEqualTo: scannedCode.lowercased())
                        
                        // Finding documents that match email and counting results
                        // Anything over 0 indicates that the person has a admin email
                        ref.getDocuments{ snapshot, error in
                            guard error == nil else{
                                print(error!.localizedDescription)
                                return
                            }
                            
                            if let snapshot = snapshot{
                                for _ in snapshot.documents {
                                    
                                    result_count += 1
                                }
                                if result_count > 0{
                                    scanned = true
                                    errorMsg = "User Exists"
                                }
                                else{
                                    errorMsg = "User does not exist"
                                }
                            }
                        }
                        
                        
                }
            }
        )
    }
    
    var body: some View {
        ZStack{
            Color.black.opacity(0.75)
            VStack(spacing: 10){
                Text(scannedCode)
                    .foregroundColor(.white)
                
                Button("Scan QR Code"){
                    self.isPresentingScanner = true
                }
                .sheet(isPresented: $isPresentingScanner){
                    self.scannerSheet
                }
                .foregroundColor(.white)
                
                Button{
                    // Add points
                    points += 1
                }
            label: {
                Text("+")
                    .bold()
                    .frame(width: 100, height: 40)
                    .foregroundColor(.white)
                    .background{
                        RoundedRectangle(cornerRadius: 20, style: .continuous)
                            .foregroundColor(.black.opacity(0.30))
                    }
            }
                
                Text(String(points))
                    .foregroundColor(.white)
                
                Button{
                    if points > 0{
                        points -= 1
                    }
                    }
                
            label: {
                Text("-")
                    .bold()
                    .frame(width: 100, height: 40)
                    .foregroundColor(.white)
                    .background{
                        RoundedRectangle(cornerRadius: 20, style: .continuous)
                            .foregroundColor(.black.opacity(0.30))
                    }
            }
                
                Button{
                    // Add points
                    if scanned{
                        dataManager.addPoints(email: scannedCode, pizzas: Int(points) )
                        dataManager.fetchPoints(email: scannedCode)
                        success = "Success!"
                    }
                    else{
                        
                        errorMsg = "Email not scanned or email not found in database"
                        success = "Something went wrong :/"
                    }
                }
            label: {
                Text("Add Points")
                    .bold()
                    .frame(width: 200, height: 40)
                    .foregroundColor(.white)
                    .background{
                        RoundedRectangle(cornerRadius: 20, style: .continuous)
                            .foregroundColor(.black.opacity(0.30))
                    }
            }
                
                Button{
                    // Redeem points
                    if scanned{
                        dataManager.redeemPoints(email: scannedCode, pizzas: Int(points) )
                        dataManager.fetchPoints(email: scannedCode)
                        success = "Success!"
                    }
                    else{
                        errorMsg = "Email not scanned or email not found in database"
                        success = "Something went wrongs :/"
                    }
                }
            label: {
                Text("Redeem Points")
                    .bold()
                    .frame(width: 200, height: 40)
                    .foregroundColor(.white)
                    .background{
                        RoundedRectangle(cornerRadius: 20, style: .continuous)
                            .foregroundColor(.black.opacity(0.30))
                    }
                }
                
                Text(errorMsg)
                    .bold()
                    .foregroundColor(.white)
                
                Text(success)
                    .bold()
                    .foregroundColor(.white)
                
            }
        }
    }
}

struct pizzaView_Previews: PreviewProvider {
    static var previews: some View {
        pizzaView()
    }
}
