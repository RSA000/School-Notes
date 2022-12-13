//
//  pizzaView.swift
//  rustic_admin
//
//  Created by Richard Andison on 2022-12-11.
//

import SwiftUI
import CodeScanner

struct pizzaView: View {
    @EnvironmentObject var dataManager: DataManager
    @State var isPresentingScanner = false
    @State var scannedCode: String = "Scanned email will appear here"
    @State var pizza_count = ""
    @State var scanned = false
    
    var scannerSheet : some View{
            CodeScannerView(
                codeTypes: [.qr],
                completion: {result in
                    if case let .success(code) = result {
                        self.scannedCode = code.string
                        self.isPresentingScanner = false
                        dataManager.fetchPoints(email: scannedCode)
                        scanned = true
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
                
                TextField("Pizzas", text: $pizza_count)
                    .padding()
                    .keyboardType(.decimalPad)
                    .placeholder(when: pizza_count.isEmpty){
                        Text("0")
                            .foregroundColor(.white)
                            .bold()
                    }
                
                Button{
                    // Add points
                    if scanned{
                        dataManager.addPoints(email: scannedCode, pizzas: Int(pizza_count) ?? 0)
                        dataManager.fetchPoints(email: scannedCode)
                    }
                    else{
                        print("Email not scanned")
                    }
                }
            label: {
                Text("Add Points")
                    .bold()
                    .frame(width: 200, height: 40)
                    .foregroundColor(.white)
                    .background{
                        RoundedRectangle(cornerRadius: 20, style: .continuous)
                            .fill(.linearGradient(colors: [.black], startPoint: .top, endPoint: .bottomTrailing)).opacity(0.30)
                    }
            }
                
                Button{
                    // Redeem points
                    if scanned{
                        dataManager.redeemPoints(email: scannedCode, pizzas: Int(pizza_count) ?? 0)
                        dataManager.fetchPoints(email: scannedCode)
                    }
                    else{
                        print("Email not scanned")
                    }
                }
            label: {
                Text("Redeem Points")
                    .bold()
                    .frame(width: 200, height: 40)
                    .foregroundColor(.white)
                    .background{
                        RoundedRectangle(cornerRadius: 20, style: .continuous)
                            .fill(.linearGradient(colors: [.black], startPoint: .top, endPoint: .bottomTrailing)).opacity(0.30)
                    }
            }
                
            }
        }
    }
}

struct pizzaView_Previews: PreviewProvider {
    static var previews: some View {
        pizzaView()
    }
}
