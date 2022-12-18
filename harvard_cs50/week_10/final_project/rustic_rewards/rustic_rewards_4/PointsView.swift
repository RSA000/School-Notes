//
//  PointsView.swift
//  rustic_rewards_4
//
//  Created by Richard Andison on 2022-12-03.
//

import SwiftUI

struct PointsView: View {
    @EnvironmentObject var dataManager: DataManager
    
    
    var body: some View {
        ZStack{
            
            Color.red.opacity(0.90)
            Text("Points Available: " + String(dataManager.pointCount - dataManager.redeemedCount))
                .frame(width: 300, height: 50)
                .foregroundColor(.white)
                .background{
                    RoundedRectangle(cornerRadius: 20, style: .continuous)
                        .foregroundColor(.gray)
                }
                .padding(.top, 50)
                .offset(y: 40)
                .aspectRatio(contentMode: .fit)
   
            
            Text("Total Points Earned: " + String(dataManager.pointCount))
                .frame(width: 300, height: 50)
                .foregroundColor(.white)
                .background{
                    RoundedRectangle(cornerRadius: 20, style: .continuous)
                        .foregroundColor(.gray)
                }
                .padding(.top, 50)
                .offset(y: 140)
                .aspectRatio(contentMode: .fit)
            
            
            Text("Total Points Redeemed: " + String(dataManager.redeemedCount))
                .frame(width: 300, height: 50)
                .foregroundColor(.white)
                .background{
                    RoundedRectangle(cornerRadius: 20, style: .continuous)
                        .foregroundColor(.gray)
                }
                .padding(.top, 50)
                .offset(y: 240)
                .aspectRatio(contentMode: .fit)
            
            
            // QR image
            Image(uiImage: UIImage(data: returnDate(str: USER_ID))!).resizable().frame(width: 275, height: 275)
                .padding(.bottom, 200)
                .padding(.top, 125)
                .offset(y: -100)
                .aspectRatio(contentMode: .fit)
        }
        .ignoresSafeArea()
    }
    
    // Grab users email and turns it into a QR Code
    func returnDate(str: String)->Data{
        let filter = CIFilter(name: "CIQRCodeGenerator")
        let data = str.data(using: .utf8, allowLossyConversion: false)
        filter?.setValue(data, forKey: "inputMessage")
        let image = filter?.outputImage?.transformed(by: CGAffineTransform(scaleX: 5, y: 5))
        let uiimage = UIImage(ciImage: image!)
        return uiimage.pngData()!
    }
}



struct PointsView_Previews: PreviewProvider {
    static var previews: some View {
        PointsView()
            .environmentObject(DataManager())
    }
}
